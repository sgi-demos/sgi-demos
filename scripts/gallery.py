#!/usr/bin/env python3
"""The gallery: every demo on exhibit, in title order.

Writes it twice, from one list:
  demos/gallery.json   read by the site's browse page (sgi-demos.org/browse/)
  README.md            the Working demos grid, between the demos:start and
                       demos:end markers (a plain HTML table: GitHub renders no CSS)

The demos are the root Makefile's list (`make list`) without variants such as
ep-1994/decomp, with title, author, and year from each placard.json, plus the
demos other sgi-demos repositories host (EXTERNAL below). Run after adding a
demo or editing a title (`make gallery`), from anywhere.
"""
import json
import os
import subprocess
import sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
from placard import SITE
COLS = 6
WIDTH = 110   # about half the browse page's card width

# Demos hosted by other sgi-demos repositories, as gallery entries
EXTERNAL = [
    {"name": "webfly", "title": "Performer Town", "sub": "Unattributed, 1993",
     "run": SITE + "/sgi-performer/web/apps/webfly/web/",
     "source": "https://github.com/sgi-demos/sgi-performer/tree/main/web/apps/webfly",
     "thumb": SITE + "/sgi-performer/media/webfly.png"},
]


def entries():
    names = subprocess.run(["make", "--no-print-directory", "-s", "-C", ROOT, "list"],
                           capture_output=True, text=True, check=True).stdout.split()
    out = list(EXTERNAL)
    for name in names:
        if "/" in name:
            continue
        with open(os.path.join(ROOT, "demos", name, "placard.json")) as fh:
            d = json.load(fh)
        out.append({"name": name, "title": d["title"],
                    "sub": ", ".join(x for x in (d.get("author", ""), d.get("year", "")) if x),
                    "run": f"{SITE}/sgi-demos/demos/{name}/web/",
                    "source": f"https://github.com/sgi-demos/sgi-demos/tree/main/demos/{name}",
                    "thumb": f"{SITE}/sgi-demos/media/{name}.png"})
    return sorted(out, key=lambda e: e["title"].lower())


def table(es):
    # two table rows per band of demos (thumbnails, then titles) so the titles
    # all start on one line however long any of them runs; each band is its own
    # table, so GitHub's table margin separates titles from the next thumbnails
    tables = []
    for i in range(0, len(es), COLS):
        band = es[i:i + COLS]
        rows = ["<tr>" + "".join(f'<td align="center"><a href="{e["run"]}"><img src="{e["thumb"]}" width="{WIDTH}" alt="{e["title"]}"></a></td>' for e in band) + "</tr>",
                "<tr>" + "".join(f'<td align="center" valign="top"><a href="{e["run"]}"><b>{e["title"]}</b></a></td>' for e in band) + "</tr>"]
        tables.append("<table>\n" + "\n".join(rows) + "\n</table>")
    return "\n\n".join(tables)


def main():
    es = entries()
    with open(os.path.join(ROOT, "demos", "gallery.json"), "w") as fh:
        json.dump(es, fh, indent=2, ensure_ascii=False)
        fh.write("\n")
    p = os.path.join(ROOT, "README.md")
    with open(p) as fh:
        s = fh.read()
    a, b = "<!-- demos:start -->", "<!-- demos:end -->"
    if a not in s or b not in s:
        sys.exit("README.md has no demos:start / demos:end markers")
    i, j = s.index(a) + len(a), s.index(b)
    with open(p, "w") as fh:
        fh.write(s[:i] + "\n" + table(es) + "\n" + s[j:])
    print("demos/gallery.json and README.md: %d demos" % len(es))


if __name__ == "__main__":
    main()
