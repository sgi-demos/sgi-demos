/*
 * Shim for IRIX <psio.h> (NeWS PostScript I/O), included by flight 1988's
 * flight.c for the ^Z iconify feature. Only the PSFILE type is referenced
 * (one never-used extern declaration); the iconize.h shim covers the rest.
 */
#ifndef PSIO_H
#define PSIO_H

#include <stdio.h>
typedef FILE PSFILE;

#endif
