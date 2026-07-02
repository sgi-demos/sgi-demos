#!/usr/bin/env python3
"""
ppm_compare.py - compare two directories of frameNNNN.ppm dumps.

Used to verify the gles2 (GPU) rasterizer against the reference (CPU)
rasterizer. Both rasterizers dump frames with identical timing semantics
when GEN_FRAME_PPM_FILES is set, so same-index frames are comparable for
demos whose animation steps per frame (e.g. insect):

    # reference (CPU) rasterizer
    cd demos/insect && GEN_FRAME_PPM_FILES=1 ./bin/insect   # then: mv frame*.ppm ref/

    # gles2 (GPU) rasterizer
    GLES2_RASTERIZER=gles2 GEN_FRAME_PPM_FILES=1 ./bin/insect # then: mv frame*.ppm gles2/

    python3 ../../scripts/ppm_compare.py ref gles2

Reports per-frame percentage of differing bytes and the channel-delta
histogram so off-by-one rounding (benign) is distinguished from structural
differences. Exits non-zero if any frame exceeds --threshold differing bytes.
"""
import sys, os, argparse
from collections import Counter


def load(path):
    d = open(path, 'rb').read()
    nl = d.index(b'\n') + 1
    hdr = d[:nl].split()
    return int(hdr[1]), int(hdr[2]), d[nl:]


def compare(a_path, b_path):
    wa, ha, pa = load(a_path)
    wb, hb, pb = load(b_path)
    if (wa, ha) != (wb, hb):
        return None, (wa, ha), (wb, hb), None
    n = min(len(pa), len(pb))
    diff = 0
    hist = Counter()
    for i in range(n):
        d = pa[i] - pb[i]
        if d:
            diff += 1
        hist[d] += 1
    return 100.0 * diff / n, (wa, ha), (wb, hb), hist


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dir_a", help="reference frame dir (e.g. 2D_CPU)")
    ap.add_argument("dir_b", help="comparison frame dir (e.g. 3D_OGLES offscreen)")
    ap.add_argument("--align", type=int, default=0, metavar="W",
                    help="drift tolerance: for each dir_a frame, compare against "
                         "the best-matching dir_b frame within +/-W (default 0 = "
                         "strict frame-aligned). Use a few frames for demos whose "
                         "animation phase drifts between independent runs.")
    ap.add_argument("--threshold", type=float, default=2.0,
                    help="max %% differing bytes per frame before failing (default 2.0)")
    ap.add_argument("--frames", type=int, default=0,
                    help="limit to first N comparable frames (0 = all)")
    args = ap.parse_args()

    names = sorted(f for f in os.listdir(args.dir_a)
                   if f.startswith("frame") and f.endswith(".ppm")
                   and os.path.exists(os.path.join(args.dir_b, f)))
    if args.frames:
        names = names[:args.frames]
    if not names:
        print("no common frames found")
        return 2

    # Map dir_a frame name -> integer index for the align window.
    def frame_num(n):
        import re
        m = re.search(r'(\d+)', n)
        return int(m.group(1)) if m else None

    b_frames = sorted(f for f in os.listdir(args.dir_b)
                      if f.startswith("frame") and f.endswith(".ppm"))

    worst = 0.0
    for name in names:
        if args.align > 0:
            # Compare against the best-matching dir_b frame within +/-align.
            n = frame_num(name)
            best = None
            for off in range(-args.align, args.align + 1):
                cand = f"frame{n + off:04d}.ppm"
                cp = os.path.join(args.dir_b, cand)
                if not os.path.exists(cp):
                    continue
                pct, sa, sb, hist = compare(os.path.join(args.dir_a, name), cp)
                if pct is None:
                    continue
                if best is None or pct < best[0]:
                    best = (pct, sa, sb, hist, cand)
            if best is None:
                print(f"{name}: no comparable dir_b frame in window")
                continue
            pct, sa, sb, hist, matched = best
            tag = f" [matched {matched}]" if matched != name else ""
        else:
            pct, sa, sb, hist = compare(os.path.join(args.dir_a, name),
                                        os.path.join(args.dir_b, name))
            tag = ""
            if pct is None:
                print(f"{name}: SIZE MISMATCH {sa} vs {sb}")
                worst = 100.0
                continue
        # off-by-one share of the *differing* channels
        differ = sum(c for d, c in hist.items() if d != 0)
        ob1 = hist.get(1, 0) + hist.get(-1, 0)
        ob1pct = (100.0 * ob1 / differ) if differ else 0.0
        worst = max(worst, pct)
        print(f"{name}: {sa[0]}x{sa[1]}  diff={pct:5.2f}%  "
              f"(off-by-1 share of diffs: {ob1pct:4.1f}%){tag}")

    print(f"\nworst frame: {worst:.2f}%  threshold: {args.threshold:.2f}%")
    if worst > args.threshold:
        print("FAIL")
        return 1
    print("PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
