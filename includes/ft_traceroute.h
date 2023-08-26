#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include "ft_libft.h"
# include "ft_utils.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <signal.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <sys/time.h>
# include <sysexits.h>
# include <errno.h>
# include <stdarg.h>
# include <limits.h>


# define PING_PACKET_SIZE   56
# define DEFAULT_TTL        64
# define MAX_HOPS			64

# define PING_PACKET_SIZE   56
# define DEFAULT_TTL        64

# define EX_HELP        0

# define OPT_HELP     (1 << 0)
# define OPT_VERBOSE  (1 << 1)
# define OPT_COUNT    (1 << 2)
# define OPT_TTL      (1 << 3)
# define OPT_TOS      (1 << 4)
# define OPT_TIMEOUT  (1 << 5)
# define OPT_QUIET    (1 << 6)

# define PORT 33434
# define TRACE_TTL 1
#define ICMP_HEADER_SIZE sizeof(struct icmphdr)

/**
 * @brief arguments struct
 * Store command line arguments
 */
typedef struct s_args {
    char	*hostname;
    int     options;
    int     ttl;
    int     tos;
    int     max_hop;
    time_t  timeout;
    int     port;
    int     count_valid;
    int     invalid_option;
} t_args;

typedef struct  s_traceroute
{
    t_args      		*args;
    int         		routine_loop;
	int					sockfd;
	int					sockfd_icmp;
	struct sockaddr_in	dest_addr;
	char 				*ip_addr;
	struct timeval 		time_before_send;
	int					times;
    char                *route_ip;
    int                 unreach;
}               t_traceroute;


/* Global Variable */
extern t_traceroute   *g_traceroute;


void    	parse_clo(int len, char *clo_args[]);
void    	traceroute_start();
uint16_t 	calculate_icmp_checksum(void *data, size_t length);
void 		create_socket();
void        traceroute_start();
void		send_icmp_packet();
int 		recv_icmp_packet(int state);
#endif