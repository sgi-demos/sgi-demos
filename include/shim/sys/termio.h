/*
 * Shim for IRIX <sys/termio.h>, included by flight 3.4's udpbrdcst.h.
 * On IRIX it dragged in the ioctl declarations (FIONBIO etc.) that
 * udpbrdcst.c relies on; provide them via the modern header.
 */
#include <sys/ioctl.h>
