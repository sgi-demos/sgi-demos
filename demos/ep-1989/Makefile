APPNAME=ep-1989
# ep.c does #include <panel.h>; the (headless) panel library lives here.
# -w: silence warnings on this frozen vintage source. Its only warnings are
# "too many arguments in call to ..." (K&R functions like load_spectrum_map()
# / regularscreen() / twixt() called with an extra, ignored arg in Tristram's
# original code) — a harmless, always-on clang diagnostic with no -Wno-<name>
# flag, so -w is the only way to quiet it without editing the original source.
DEMO_CFLAGS=-I. -w
include ../../makefiles/make_demo.mk
