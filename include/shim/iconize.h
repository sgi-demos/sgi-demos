/*
 * Shim for flight 1988's generated iconize.h. The original was produced by
 * the IRIX cps compiler from iconize.cps (a NeWS PostScript snippet that
 * iconifies the window; "thanks to Mark Callow for the code"). There is no
 * window system iconify here, so flipiconic() is a no-op.
 */
#ifndef ICONIZE_H
#define ICONIZE_H

static void flipiconic(int gid) { (void)gid; }

#endif
