#ifndef SYS_IOCTL_SHIM_H_
#define SYS_IOCTL_SHIM_H_

#if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif

// POSIX <sys/ioctl.h> for Windows, for include/shim/sys/termio.h: the
// non-blocking socket request flight 3.4's dogfight code makes (see
// sys/socket.h here). ioctl() is a stub that fails with ENOSYS.
#define FIONBIO 0x8004667e

int ioctl(int fd, unsigned long request, ...);

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // SYS_IOCTL_SHIM_H_
