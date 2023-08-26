# include "ft_traceroute.h"


/** @Brief Socket Creation
 * Creates a raw socket for sending and receiving ICMP packets.
 *
 * @return none
*/
void create_socket()
{
    struct timeval timeout;

    timeout.tv_sec = g_traceroute->args->timeout;
    timeout.tv_usec = 0;
    // Create a UDP socket
    g_traceroute->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (g_traceroute->sockfd == -1)
        show_errors("Error: creating raw socket failed!\n", EX_OSERR);

    int val = 2;
    if (setsockopt(g_traceroute->sockfd, IPPROTO_IP, IP_MTU_DISCOVER, &val, sizeof(val)) == -1)
        show_errors("Error: setsockopt failed!\n", EX_OSERR);
    if (setsockopt(g_traceroute->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
        show_errors("Error: setsockopt failed!\n", EX_OSERR);

    /* TO-DO: Create raw socket */
    g_traceroute->sockfd_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (g_traceroute->sockfd < 0)
        show_errors("Error: creating raw socket failed!\n", EX_OSERR);


    if (setsockopt(g_traceroute->sockfd_icmp, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
        show_errors("Error: setsockopt failed!\n", EX_OSERR);
    if (setsockopt(g_traceroute->sockfd, IPPROTO_IP, IP_TOS, &g_traceroute->args->tos, sizeof(g_traceroute->args->tos)) == -1)
        show_errors("Error: setsockopt failed!\n", EX_OSERR);
    return ;
}