#!/usr/bin/env python3
"""Gallery placards for the demos.

Each demo carries demos/<name>/placard.json: the text shown as a fading
overlay when the demo starts (web) or printed to the terminal (native).

  scripts/placard.py scan  <demo-dir>        print the inputs found in the source
  scripts/placard.py update [<demo-dir>...]  write them into placard.json as "inputs_detected"
  scripts/placard.py embed <placard.json>    emit a C file that prints the placard at startup (used by make_demo.mk)

The scan is a heuristic over the IRIS GL event calls: qdevice(), getbutton(),
getvaluator(), the character literals a qdevice(KEYBD) demo compares against,
and Panel Library actuator keys. It reports which inputs exist, not what they
do. A hand-written "inputs" list in placard.json takes precedence on the page.
"""
import json
import os
import re
import sys

# IRIS GL device -> (group, label). Groups are shown in this order.
GROUPS = ["mouse", "keys", "keypad", "dials", "spaceball"]
DEVICES = {
    "LEFTMOUSE": ("mouse", "L"), "MOUSE3": ("mouse", "L"),
    "MIDDLEMOUSE": ("mouse", "M"), "MOUSE2": ("mouse", "M"),
    "RIGHTMOUSE": ("mouse", "R"), "MOUSE1": ("mouse", "R"),
    "MENUBUTTON": ("mouse", "R"),
    "MOUSEX": ("mouse", "drag"), "MOUSEY": ("mouse", "drag"),
    "ESCKEY": ("keys", "esc"), "SPACEKEY": ("keys", "space"), "RETKEY": ("keys", "return"),
    "HOMEKEY": ("keys", "home"), "ENDKEY": ("keys", "end"), "PAUSEKEY": ("keys", "pause"),
    "INSERTKEY": ("keys", "insert"), "DELKEY": ("keys", "delete"), "TABKEY": ("keys", "tab"),
    "BACKSPACEKEY": ("keys", "backspace"),
    "LEFTSHIFTKEY": ("keys", "shift"), "RIGHTSHIFTKEY": ("keys", "shift"),
    "CTRLKEY": ("keys", "ctrl"), "LEFTCTRLKEY": ("keys", "ctrl"), "RIGHTCTRLKEY": ("keys", "ctrl"),
    "LEFTALTKEY": ("keys", "alt"), "RIGHTALTKEY": ("keys", "alt"),
    "UPARROWKEY": ("keys", "arrow keys"), "DOWNARROWKEY": ("keys", "arrow keys"),
    "LEFTARROWKEY": ("keys", "arrow keys"), "RIGHTARROWKEY": ("keys", "arrow keys"),
    "PAGEUPKEY": ("keys", "page up/down"), "PAGEDOWNKEY": ("keys", "page up/down"),
}
IGNORE = {"REDRAW", "INPUTCHANGE", "WINQUIT", "WINSHUT", "WINFREEZE", "WINTHAW", "TIMER0", "TIMER1",
          "TIMER2", "TIMER3", "KEYBD", "REDRAWICONIC", "DEPTHCHANGE", "WINCLOSE", "QFULL"}
RE_DEV = re.compile(r"\b(?:qdevice|getbutton|getvaluator|unqdevice)\s*\(\s*([A-Z][A-Z0-9_]*)\s*\)")
RE_CASE = re.compile(r"case\s*'(\\?.)'\s*:")
RE_EQ = re.compile(r"==\s*'(\\?.)'")
RE_PNL = re.compile(r"\bkey\s*=\s*'(\\?.)'")
RE_PNL_DEV = re.compile(r"->\s*key\s*=\s*([A-Z])KEY\b")   # Panel Library actuators: button->key = OKEY


def sources(demo_dir):
    for root, _dirs, files in os.walk(demo_dir):
        rel = os.path.relpath(root, demo_dir)
        if rel.split(os.sep)[0] in ("bin", "web", "original", "versions", "archive") or "bin-" in rel:
            continue
        for f in files:
            # the port's own harness files (main_sgi.c) count: they define the port's inputs
            if f.endswith((".c", ".h")) and not f.startswith(("panelstub", "epscript", "gl_wrap", "parser.tab", "lexer")):
                yield os.path.join(root, f)


def scan(demo_dir):
    text = {}
    for path in sources(demo_dir):
        try:
            with open(path, encoding="latin-1") as fh:
                text[path] = fh.read()
        except OSError:
            pass
    found = {g: set() for g in GROUPS}
    chars = set()
    uses_keybd = False
    for src in text.values():
        for dev in RE_DEV.findall(src):
            if dev == "KEYBD":
                uses_keybd = True
                continue
            if dev in IGNORE:
                continue
            if dev in DEVICES:
                g, label = DEVICES[dev]
                found[g].add(label)
            elif re.fullmatch(r"[A-Z]KEY", dev):
                found["keys"].add(dev[0])
            elif re.fullmatch(r"F\d+KEY", dev):
                found["keys"].add(dev[:-3])
            elif re.fullmatch(r"(ZERO|ONE|TWO|THREE|FOUR|FIVE|SIX|SEVEN|EIGHT|NINE)KEY", dev):
                found["keys"].add(dev[:-3].lower())
            elif dev.startswith("PAD"):
                found["keypad"].add("keypad")
            elif dev.startswith("DIAL") or dev.startswith("SW") or dev.startswith("BUT"):
                found["dials"].add("dial box")
            elif dev.startswith("SB"):
                found["spaceball"].add("spaceball")
        for m in RE_PNL.findall(src):
            chars.add(m)
        for m in RE_PNL_DEV.findall(src):
            found["keys"].add(m)
    if uses_keybd:
        for src in text.values():
            for m in RE_CASE.findall(src) + RE_EQ.findall(src):
                chars.add(m)
    printable = sorted(c for c in chars if len(c) == 1 and c.isprintable() and not c.isspace())
    if "\\033" in chars or "\\33" in chars or "\\e" in chars:
        found["keys"].add("esc")
    if " " in chars:
        found["keys"].add("space")
    letters = sorted({c.upper() for c in printable if c.isalpha()} | {c for c in found["keys"] if len(c) == 1})
    others = [c for c in printable if not c.isalpha()]
    out = []
    # mouse: buttons then motion ("mouse: L M R drag"). Motion is reported as
    # drag: the demos read MOUSEX/MOUSEY to steer while a button is held, and
    # the scan can't tell a plain move apart anyway
    if found["mouse"]:
        out.append("mouse: " + " ".join(m for m in ["L", "M", "R", "drag"] if m in found["mouse"]))
    # keys, comma separated, no prefix: named keys (lower case) in a fixed
    # order, then function keys, letters (upper case), symbols
    named = ["esc", "space", "return", "tab", "backspace", "arrow keys", "page up/down", "home", "end", "insert", "delete", "pause", "shift", "ctrl", "alt"]
    keys = [k for k in named if k in found["keys"]]
    keys += sorted((k for k in found["keys"] if k.startswith("F") and k[1:].isdigit()), key=lambda k: int(k[1:]))
    keys += letters + others
    if keys:
        out.append(", ".join(keys))
    for g in ("keypad", "dials", "spaceball"):
        out.extend(sorted(found[g]))
    return out


def demo_dirs(args):
    if args:
        return args
    root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "demos")
    return sorted(os.path.join(root, d) for d in os.listdir(root) if os.path.isdir(os.path.join(root, d)))


def c_string(s):
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n") + '"'


def main(argv):
    if len(argv) < 2:
        sys.exit(__doc__)
    cmd = argv[1]
    if cmd == "scan":
        for d in demo_dirs(argv[2:]):
            print(os.path.basename(os.path.abspath(d)) + ": " + ", ".join(scan(d)))
    elif cmd == "update":
        for d in demo_dirs(argv[2:]):
            p = os.path.join(d, "placard.json")
            if not os.path.exists(p):
                continue
            with open(p) as fh:
                data = json.load(fh)
            data["inputs_detected"] = scan(d)
            with open(p, "w") as fh:
                json.dump(data, fh, indent=2, ensure_ascii=False)
                fh.write("\n")
            print(os.path.basename(os.path.abspath(d)) + ": " + ", ".join(data["inputs_detected"]))
    elif cmd == "embed":
        # A C file defining gl_placard: the placard as plain text lines, or
        # NULL when the demo has no placard.json. Native builds print it at
        # winopen; the web pages read placard.json themselves.
        p = argv[2]
        # A C file that prints the placard to the terminal before main() runs
        # (native only; the web pages read placard.json themselves), unless
        # SGI_PLACARD=0. Self-contained: libgl and the demo know nothing of it.
        print("/* generated by scripts/placard.py from placard.json; do not edit */")
        if not os.path.exists(p):
            print("/* no placard.json for this demo */")
            return
        with open(p) as fh:
            data = json.load(fh)
        lines = [data.get("title", "")]
        who = ", ".join(x for x in (data.get("author", ""), data.get("year", "")) if x)
        fb = ", ".join(y for y in (data.get("color", ""), data.get("depth", "")) if y)
        line = " / ".join(x for x in (who, fb, data.get("machines", "")) if x)
        if line:
            lines.append(line)
        if data.get("blurb"):
            lines.append("")
            lines.append(data["blurb"])
        inputs = data.get("inputs") or data.get("inputs_detected") or []
        if inputs:
            lines.append("")
            lines.append("Inputs: " + "; ".join(inputs))
        print("#ifndef __EMSCRIPTEN__")
        print("#include <stdio.h>")
        print("#include <stdlib.h>")
        print("__attribute__((constructor)) static void placard_print(void)")
        print("{")
        print('    const char *v = getenv("SGI_PLACARD");')
        print("    if (v && atoi(v) == 0) return;")
        print('    printf("\\n%s\\n(SGI_PLACARD=0 hides this placard)\\n\\n", ' + c_string("\n".join(lines)) + ");")
        print("    fflush(stdout);")
        print("}")
        print("#endif")
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main(sys.argv)
