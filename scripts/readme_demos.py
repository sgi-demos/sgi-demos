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
import sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
SITE = "https://sgi-demos.org"
RUN = SITE + "/sgi-demos/demos/{name}/web/"
THUMB = SITE + "/sgi-demos/media/{name}.png"
COLS = 6
WIDTH = 110   # about half the browse page's card width

# Demos hosted by other sgi-demos repositories: name, title, year, run URL, thumbnail
EXTRA = [
    ("webfly", "Performer Town", "1993", SITE + "/sgi-performer/web/apps/webfly/web/", SITE + "/sgi-performer/media/webfly.png"),
]
# the order of the browse page
ORDER = ["arena", "bounce", "buttonfly", "cedit", "ep-1988", "ep-1989", "ep-1994-ogl-decomp", "ep-1994-ogl-reversed",
         "flight-1988", "flight-1994", "gview", "ideas", "insect", "jello", "logo", "newave", "webfly", "twilight"]


def entries():
    out = []
    extra = {e[0]: e for e in EXTRA}
    for name in ORDER:
        if name in extra:
            _, title, year, run, thumb = extra[name]
        else:
            with open(os.path.join(ROOT, "demos", name, "placard.json")) as fh:
                d = json.load(fh)
            title, year = d["title"], d.get("year", "")
            run, thumb = RUN.format(name=name), THUMB.format(name=name)
        out.append((title, year, run, thumb))
    return out


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
    print("README.md: %d demos" % len(ORDER))


if __name__ == "__main__":
    main()
