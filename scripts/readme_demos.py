#!/usr/bin/env python3
"""Regenerate the Working demos grid in README.md from the placards.

Each demos/<name>/placard.json supplies the title; the thumbnail is
media/<name>.png and the demo runs at sgi-demos.org/sgi-demos/demos/<name>/web/.
The grid is the README-sized cousin of sgi-demos.org/browse/, which reads the
same placard files, so the two never disagree. GitHub renders no CSS, so the
grid is a plain HTML table. Run from anywhere:

  scripts/readme_demos.py          rewrites README.md between the demos:start / demos:end markers
"""
import json
import os
import subprocess
import sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
from placard import SITE
RUN = SITE + "/sgi-demos/demos/{name}/web/"
THUMB = SITE + "/sgi-demos/media/{name}.png"
COLS = 6
WIDTH = 110   # about half the browse page's card width

# Demos hosted by other sgi-demos repositories: name, title, year, run URL, thumbnail
EXTRA = [
    ("webfly", "Performer Town", "1993", SITE + "/sgi-performer/web/apps/webfly/web/", SITE + "/sgi-performer/media/webfly.png"),
]


def entries():
    # the demos are the root Makefile's list, without variants (ep-1994/decomp),
    # plus EXTRA; in title order, like the browse page
    names = subprocess.run(["make", "--no-print-directory", "-s", "-C", ROOT, "list"],
                           capture_output=True, text=True, check=True).stdout.split()
    out = [e[1:] for e in EXTRA]
    for name in names:
        if "/" in name:
            continue
        with open(os.path.join(ROOT, "demos", name, "placard.json")) as fh:
            d = json.load(fh)
        out.append((d["title"], d.get("year", ""), RUN.format(name=name), THUMB.format(name=name)))
    return sorted(out, key=lambda e: e[0].lower())


def table():
    # two table rows per band of demos (thumbnails, then titles) so the titles
    # all start on one line however long any of them runs
    # each band is its own table, so GitHub's table margin puts clear space
    # between a row of titles and the next row of thumbnails
    es = entries()
    tables = []
    for i in range(0, len(es), COLS):
        band = es[i:i + COLS]
        rows = ["<tr>" + "".join(f'<td align="center"><a href="{run}"><img src="{thumb}" width="{WIDTH}" alt="{title}"></a></td>' for title, year, run, thumb in band) + "</tr>",
                "<tr>" + "".join(f'<td align="center" valign="top"><a href="{run}"><b>{title}</b></a></td>' for title, year, run, thumb in band) + "</tr>"]
        tables.append("<table>\n" + "\n".join(rows) + "\n</table>")
    return "\n\n".join(tables)


def main():
    p = os.path.join(ROOT, "README.md")
    with open(p) as fh:
        s = fh.read()
    a, b = "<!-- demos:start -->", "<!-- demos:end -->"
    if a not in s or b not in s:
        sys.exit("README.md has no demos:start / demos:end markers")
    i, j = s.index(a) + len(a), s.index(b)
    s = s[:i] + "\n" + table() + "\n" + s[j:]
    with open(p, "w") as fh:
        fh.write(s)
    print("README.md: %d demos" % len(entries()))


if __name__ == "__main__":
    main()
