#!/bin/sh
# Flatten the repository's source into one Markdown file, docs/REPO.md
# (gitignored), for reading or searching in one place. Left out: the docs,
# the scripts, every web/ build package (Emscripten .js, .wasm, .data, and the
# generated index.html), demo data files (flight-1994's defs/, gview's .gfo
# models), the Khronos and ANGLE headers and binaries in libs/libgles/, the
# smoke test images, and uuencoded archive copies. Run from anywhere.
cd "$(dirname "$0")/.." || exit 1
npx repomix . --style markdown \
    --ignore 'docs/**,scripts/**,**/web/**,demos/flight-1994/defs/**,**/*.gfo,libs/libgles/**,tests/smoke/results/**,tests/smoke/baseline/**,tests/smoke/report/**,media/**,**/*uue*.txt' \
    --output docs/REPO.md
