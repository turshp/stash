#include "../config.h"

#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */

#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> /* bzero() */

/* *INDENT-OFF* */
#ifndef INET_ADDRSTRLEN
/* $$.Ic INET_ADDRSTRLEN$$ */
#define	INET_ADDRSTRLEN		16	/* "ddd.ddd.ddd.ddd\0"
								    1234567890123456 */
#endif

/* Define following even if IPv6 not supported, so we can always allocate
   an adequately sized buffer without #ifdefs in the code. */
#ifndef INET6_ADDRSTRLEN
/* $$.Ic INET6_ADDRSTRLEN$$ */
#define	INET6_ADDRSTRLEN	46	/* max size of IPv6 address string:
				   "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx" or
				   "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\0"
				    1234567890123456789012345678901234567890123456 */
#endif
/* *INDENT-ON* */

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* Define some port number that can be used for our examples */
#define	SERV_PORT		 9877			/* TCP and UDP */
#define	SERV_PORT_STR	"9877"			/* TCP and UDP */
#define	UNIXSTR_PATH	"/tmp/unix.str"	/* Unix domain stream */
#define	UNIXDG_PATH		"/tmp/unix.dg"	/* Unix domain datagram */

/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

void Close(int);
void Write(int, void *, size_t);


/* prototypes for our socket wrapper functions: see {Sec errors} */
int  Accept(int, SA *, socklen_t *);
void Bind(int, const SA *, socklen_t);
void Connect(int, const SA *, socklen_t);
void Getpeername(int, SA *, socklen_t *);
void Getsockname(int, SA *, socklen_t *);
void Getsockopt(int, int, int, void *, socklen_t *);
/*#ifdef	HAVE_INET6_RTH_INIT
int  Inet6_rth_space(int, int);
void *Inet6_rth_init(void *, socklen_t, int, int);
void Inet6_rth_add(void *, const struct in6_addr *);
void Inet6_rth_reverse(const void *, void *);
int  Inet6_rth_segments(const void *);
struct in6_addr *Inet6_rth_getaddr(const void *, int);
#endif
#ifdef HAVE_KQUEUE
int  Kqueue(void);
int  Kevent(int, const struct kevent *, int,
		struct kevent *, int, const struct timespec *);
#endif*/
void Listen(int, int);
//#ifdef	HAVE_POLL
//int  Poll(struct pollfd *, unsigned long, int);
//#endif
//ssize_t	 Readline(int, void *, size_t);
//ssize_t	 Readn(int, void *, size_t);
//ssize_t	 Recv(int, void *, size_t, int);
//ssize_t	 Recvfrom(int, void *, size_t, int, SA *, socklen_t *);
//ssize_t	 Recvmsg(int, struct msghdr *, int);
//int		 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
//void	 Send(int, const void *, size_t, int);
//void	 Sendto(int, const void *, size_t, int, const SA *, socklen_t);
//void	 Sendmsg(int, const struct msghdr *, int);
//void	 Setsockopt(int, int, int, const void *, socklen_t);
//void	 Shutdown(int, int);
//int		 Sockatmark(int);
int		 Socket(int, int, int);
//void	 Socketpair(int, int, int, int *);
//void	 Writen(int, void *, size_t);


/* related to system call, i.e. print strerror(errno) */
void err_ret(const char *, ...);
void err_sys(const char *, ...);
void err_dump(const char *, ...);
/* unrelated to system call */
void err_msg(const char *, ...);
void err_quit(const char *, ...);

