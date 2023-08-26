#include "ft_traceroute.h"


/** @Brief Send ICMP Packet
 * Constructs and sends an ICMP packet to the target host.
 *
 * @return none
 */
void send_icmp_packet()
{
    // Send a UDP packet to the destination
    char message[33];

    ft_bzero(message, sizeof(message));
    for (int i = 0; i < 32;i++)
        message[i] = 'A';
    gettimeofday(&g_traceroute->time_before_send, NULL);
    if (sendto(g_traceroute->sockfd, message, strlen(message), 0,
               (struct sockaddr *)&g_traceroute->dest_addr, sizeof(g_traceroute->dest_addr)) == -1)
        show_errors("Error: sendto failed!\n", EX_OSERR);
    return ;
}