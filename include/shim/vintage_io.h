/*
 * Prototypes vintage K&R code leaves implicit but that modern ABIs need
 * declared: lseek's off_t is 64-bit on both macOS and Emscripten's musl, so
 * an implicit int-returning declaration traps wasm's call-signature checking.
 * (Not <unistd.h>: macOS's declares setmode(), colliding with libgobj's.)
 */
#ifndef VINTAGE_IO_H
#define VINTAGE_IO_H

#include <sys/types.h>

extern off_t lseek(int fd, off_t offset, int whence);

#endif
