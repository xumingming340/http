/* include unph */
/* Our own header.  Tabs are set for 4 spaces, not 8 */

#ifndef	__UNIX_INC_H_
#define	__UNIX_INC_H_

/* If anything changes in the following list of #includes, must change
   acsite.m4 also, for configure's tests. */

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<netinet/tcp.h>
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
#include	<sys/select.h>	/* for convenience */
#include	<sys/param.h>	/* OpenBSD prereq for sysctl.h */
#include	<sys/sysctl.h>
#include	<sys/ioctl.h>
#include	<poll.h>		/* for convenience */
#include	<strings.h>		/* for convenience */
#include	<pthread.h>
#include 	<getopt.h>

typedef unsigned char *byte_pointer;

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff	/* should have been in <netinet/in.h> */
#endif

#ifndef	SHUT_RD				/* these three POSIX names are new */
#define	SHUT_RD		0		/* shutdown for reading */
#define	SHUT_WR		1		/* shutdown for writing */
#define	SHUT_RDWR	2		/* shutdown for reading and writing */
#endif

#ifndef INET_ADDRSTRLEN
#define	INET_ADDRSTRLEN		16	/* "ddd.ddd.ddd.ddd\0" */
#endif

#ifndef INET6_ADDRSTRLEN
#define	INET6_ADDRSTRLEN	46	/* max size of IPv6 address string:
				   "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx" or
				   "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\0"
				    1234567890123456789012345678901234567890123456 */
#endif

#define HAVE_BZERO
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
#endif

#if	defined(sun) && defined(__GNUC__) && defined(GCC_STRUCT_PROBLEM)
#define	INET_NTOA(foo)	inet_ntoa(&foo)
#else
#define	INET_NTOA(foo)	inet_ntoa(foo)
#endif

/* The structure returned by recvfrom_flags() */
struct unp_in_pktinfo {
  struct in_addr	ipi_addr;	/* dst IPv4 address */
  int				ipi_ifindex;/* received interface index */
};

#ifndef	CMSG_LEN
#define	CMSG_LEN(size)		(sizeof(struct cmsghdr) + (size))
#endif
#ifndef	CMSG_SPACE
#define	CMSG_SPACE(size)	(sizeof(struct cmsghdr) + (size))
#endif


#ifndef	SUN_LEN
#define	SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

#ifndef	AF_LOCAL
#define AF_LOCAL	AF_UNIX
#endif
#ifndef	PF_LOCAL
#define PF_LOCAL	PF_UNIX
#endif


#ifndef INFTIM
#define INFTIM          (-1)    /* infinite poll timeout */
#define	INFTIM_UNPH				/* tell unpxti.h we defined it */
#endif

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

#define	SA	struct sockaddr

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */

typedef	void	Sigfunc(int);	/* for signal handlers */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

/*********************************************  this from understand computer system */
#define RIO_BUFSIZE 8192
typedef struct {
    int rio_fd;                /* descriptor for this internal buf */
    int rio_cnt;               /* unread bytes in internal buf */
    char *rio_bufptr;          /* next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* internal buffer */
} rio_t;
/****************************************************************************/

ssize_t		rio_readn(int fd, void *usrbuf, size_t n);
ssize_t 	rio_writen(int fd, void *usrbuf, size_t n);
void 		rio_readinitb(rio_t *rp, int fd);
ssize_t 	rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t 	rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/* Wrappers for Rio package */
ssize_t 	Rio_readn(int fd, void *usrbuf, size_t n);
void 		Rio_writen(int fd, void *usrbuf, size_t n);
void 		Rio_readinitb(rio_t *rp, int fd);
ssize_t 	Rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t 	Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/*********************************************  this from understand computer system */

/* prototypes for our own library functions */
int		connect_nonb(int, const SA *, socklen_t, int);
int		connect_timeo(int, const SA *, socklen_t, int);
int		daemon_init(const char *, int);
void	daemon_inetd(const char *, int);
void	dg_cli(FILE *, int, SA *, socklen_t);
void	dg_echo(int, SA *, socklen_t);
int		family_to_level(int);
char	*gf_time(void);
void	heartbeat_cli(int, int, int);
void	heartbeat_serv(int, int, int);
struct addrinfo *host_serv(const char *, const char *, int, int);
int		inet_srcrt_add(char *);
u_char	*inet_srcrt_init(int);
void	inet_srcrt_print(u_char *, int);
void	inet6_srcrt_print(void *);
char	**my_addrs(int *);
int		readable_timeo(int, int);
ssize_t	readline(int, void *, size_t);
ssize_t	readn(int, void *, size_t);
ssize_t	read_fd(int, void *, size_t, int *);
ssize_t	recvfrom_flags(int, void *, size_t, int *, SA *, socklen_t *, struct unp_in_pktinfo *);
Sigfunc	*signal_intr(int, Sigfunc *);
int		sock_bind_wild(int, int);
int		sock_cmp_addr(const SA *, const SA *, socklen_t);
int		sock_cmp_port(const SA *, const SA *, socklen_t);
int		sock_get_port(const SA *, socklen_t);
void	sock_set_addr(SA *, socklen_t, const void *);
void	sock_set_port(SA *, socklen_t, int);
void	sock_set_wild(SA *, socklen_t);
char	*sock_ntop(const SA *, socklen_t);
char	*sock_ntop_host(const SA *, socklen_t);
int		sockfd_to_family(int);
void	str_echo(int sockfd, SA* cliaddr, socklen_t clilen);
void	str_cli(FILE *, int);
int		tcp_connect(const char *, const char *);
int		tcp_listen(const char *, const char *, socklen_t *);
void	tv_sub(struct timeval *, struct timeval *);
int		udp_client(const char *, const char *, SA **, socklen_t *);
int		udp_connect(const char *, const char *);
int		udp_server(const char *, const char *, socklen_t *);
int		writable_timeo(int, int);
ssize_t	writen(int, const void *, size_t);
ssize_t	write_fd(int, void *, size_t, int);

#ifdef	MCAST
int		 mcast_leave(int, const SA *, socklen_t);
int		 mcast_join(int, const SA *, socklen_t, const char *, u_int);
int		 mcast_leave_source_group(int sockfd, const SA *src, socklen_t srclen,
								  const SA *grp, socklen_t grplen);
int		 mcast_join_source_group(int sockfd, const SA *src, socklen_t srclen,
								 const SA *grp, socklen_t grplen,
								 const char *ifname, u_int ifindex);
int		 mcast_block_source(int sockfd, const SA *src, socklen_t srclen,
							const SA *grp, socklen_t grplen);
int		 mcast_unblock_source(int sockfd, const SA *src, socklen_t srclen,
							  const SA *grp, socklen_t grplen);
int		 mcast_get_if(int);
int		 mcast_get_loop(int);
int		 mcast_get_ttl(int);
int		 mcast_set_if(int, const char *, u_int);
int		 mcast_set_loop(int, int);
int		 mcast_set_ttl(int, int);

void	 Mcast_leave(int, const SA *, socklen_t);
void	 Mcast_join(int, const SA *, socklen_t, const char *, u_int);
void	 Mcast_leave_source_group(int sockfd, const SA *src, socklen_t srclen,
								  const SA *grp, socklen_t grplen);
void	 Mcast_join_source_group(int sockfd, const SA *src, socklen_t srclen,
								 const SA *grp, socklen_t grplen,
								 const char *ifname, u_int ifindex);
void	 Mcast_block_source(int sockfd, const SA *src, socklen_t srclen,
							const SA *grp, socklen_t grplen);
void	 Mcast_unblock_source(int sockfd, const SA *src, socklen_t srclen,
							  const SA *grp, socklen_t grplen);
int		 Mcast_get_if(int);
int		 Mcast_get_loop(int);
int		 Mcast_get_ttl(int);
void	 Mcast_set_if(int, const char *, u_int);
void	 Mcast_set_loop(int, int);
void	 Mcast_set_ttl(int, int);
#endif

uint16_t	in_cksum(uint16_t *, int);


			/* prototypes for our own library wrapper functions */
void	 Connect_timeo(int, const SA *, socklen_t, int);
int		 Family_to_level(int);
struct addrinfo *Host_serv(const char *, const char *, int, int);
const char		*Inet_ntop(int, const void *, char *, size_t);
void			 Inet_pton(int, const char *, void *);
char			*If_indextoname(unsigned int, char *);
unsigned int		 If_nametoindex(const char *);
struct if_nameindex	*If_nameindex(void);
char   **My_addrs(int *);
ssize_t	 Read_fd(int, void *, size_t, int *);
int		 Readable_timeo(int, int);
ssize_t	 Recvfrom_flags(int, void *, size_t, int *, SA *, socklen_t *,
		 struct unp_in_pktinfo *);
Sigfunc *Signal(int, Sigfunc *);
Sigfunc *Signal_intr(int, Sigfunc *);
int		 Sock_bind_wild(int, int);
char	*Sock_ntop(const SA *, socklen_t);
char	*Sock_ntop_host(const SA *, socklen_t);
int		 Sockfd_to_family(int);
int		 Tcp_connect(const char *, const char *);
int		 Tcp_listen(const char *, const char *, socklen_t *);
int		 Udp_client(const char *, const char *, SA **, socklen_t *);
int		 Udp_connect(const char *, const char *);
int		 Udp_server(const char *, const char *, socklen_t *);
ssize_t	 Write_fd(int, void *, size_t, int);
int		 Writable_timeo(int, int);

			/* prototypes for our Unix wrapper functions: see {Sec errors} */
void	*Calloc(size_t, size_t);
void	 Close(int);
void	 Dup2(int, int);
int		 Fcntl(int, int, int);
void	 Gettimeofday(struct timeval *, void *);
int		 Ioctl(int, int, void *);
pid_t	 Fork(void);
void	*Malloc(size_t);
int	 	Mkstemp(char *);
void	*Mmap(void *, size_t, int, int, int, off_t);
int		 Open(const char *, int, mode_t);
void	 Pipe(int *fds);
ssize_t	 Read(int, void *, size_t);
void	 Sigaddset(sigset_t *, int);
void	 Sigdelset(sigset_t *, int);
void	 Sigemptyset(sigset_t *);
void	 Sigfillset(sigset_t *);
int		 Sigismember(const sigset_t *, int);
void	 Sigpending(sigset_t *);
void	 Sigprocmask(int, const sigset_t *, sigset_t *);
char	*Strdup(const char *);
long	 Sysconf(int);
void	 Sysctl(int *, u_int, void *, size_t *, void *, size_t);
void	 Unlink(const char *);
pid_t	 Wait(int *);
pid_t	 Waitpid(pid_t, int *, int);
void	 Write(int, void *, size_t);

			/* prototypes for our stdio wrapper functions: see {Sec errors} */
void	 Fclose(FILE *);
FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);

			/* prototypes for our socket wrapper functions: see {Sec errors} */
int 	Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void	Bind(int, const SA *, socklen_t);
void	Connect(int, const SA *, socklen_t);
void	Getpeername(int, SA *, socklen_t *);
void	Getsockname(int, SA *, socklen_t *);
void	Getsockopt(int, int, int, void *, socklen_t *);
int		Inet6_rth_space(int, int);
void	*Inet6_rth_init(void *, socklen_t, int, int);
void	Inet6_rth_add(void *, const struct in6_addr *);
void	Inet6_rth_reverse(const void *, void *);
int		Inet6_rth_segments(const void *);
struct 	in6_addr *Inet6_rth_getaddr(const void *, int);
void	Listen(int, int);
int		Poll(struct pollfd *, unsigned long, int);
ssize_t	Readline(int, void *, size_t);
ssize_t	Readn(int, void *, size_t);
ssize_t	Recv(int, void *, size_t, int);
ssize_t	Recvfrom(int, void *, size_t, int, SA *, socklen_t *);
ssize_t	Recvmsg(int, struct msghdr *, int);
int		Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	Send(int, const void *, size_t, int);
void	Sendto(int, const void *, size_t, int, const SA *, socklen_t);
void	Sendmsg(int, const struct msghdr *, int);
void	Setsockopt(int, int, int, const void *, socklen_t);
void	Shutdown(int, int);
int		Sockatmark(int);
int		Socket(int, int, int);
void	Socketpair(int, int, int, int *);
void	Writen(int, void *, size_t);

void	err_dump(const char *, ...);
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);

int 	gethostent_a(const char *argv, char *hostname, int len);

#endif	/* __unp_h */

