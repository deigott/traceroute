#include "ft_traceroute.h"

#define SPEED_OF_LIGHT_KM_PER_S 200000.0



char	*perform_reverse_dns(struct iphdr *ip_header)
{
	struct sockaddr_in sa;
    char *host;

	host = (char *)malloc(sizeof(char) * 1024);
	if (host == NULL)
		show_errors("ERROR: can't allocate memory!\n", EX_OSERR);

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = ip_header->saddr;
   	getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, 1024, NULL, 0, 0);
    
	return (host);
}

/** @Brief Receive ICMP Packet
 * Receives and processes incoming ICMP packets.
 *
 * @return none
 */
int recv_icmp_packet(int state)
{
    struct sockaddr_in sender_addr;
    socklen_t sender_addr_len = sizeof(sender_addr);
    struct icmphdr *icmp_response;
    struct iphdr *ip_header;
    char buffer[IP_MAXPACKET];
    struct timeval end_time;
    ssize_t bytes_received;
    double latency; 

    bytes_received = 0;
    if (g_traceroute->args->timeout != 0)
        bytes_received = recvfrom(g_traceroute->sockfd_icmp, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
    gettimeofday(&end_time, NULL);
    latency = (double)(end_time.tv_sec - g_traceroute->time_before_send.tv_sec) * 1000.0 + (end_time.tv_usec - g_traceroute->time_before_send.tv_usec) / 1000.0;
    ip_header = (struct iphdr *)buffer;
    icmp_response = (struct icmphdr *)(buffer + ip_header->ihl * 4);
    char src[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip_header->saddr, src, INET_ADDRSTRLEN);
    if (icmp_response->type == ICMP_DEST_UNREACH && icmp_response->code == 1)
        g_traceroute->unreach = 1;
    if (bytes_received == -1 || g_traceroute->args->timeout == 0)
    {
        if (state == 2)
            write(1, "* \n", 3);
        else
            write(1, "*  ", 3);
        return (1);
    }
    if (icmp_response->type == ICMP_TIME_EXCEEDED || icmp_response->type == ICMP_DEST_UNREACH)
    {
        if (state == 0)
        {
          
            char *ip = perform_reverse_dns(ip_header);
            char *string = concatenate_strings("%s  ", src);
            ft_putstr(&string);
            free(ip);
            ip = NULL;
            g_traceroute->route_ip = ft_strdup(src);
        }
        if (state != 0 && g_traceroute->route_ip == NULL)
        {
            char *str = concatenate_strings("%s  ", src);
            ft_putstr(&str);
            g_traceroute->route_ip = ft_strdup(src);
        }
        if (state == 2)
        {
            char *string = concatenate_strings("%.3fms", (float)latency);
            ft_putstr(&string);
            if (icmp_response->type == ICMP_DEST_UNREACH && icmp_response->code == 1)
                write(1, " !H \n", 5);
            else
                write(1, " \n", 2);
            if (g_traceroute->route_ip)
            {
                free(g_traceroute->route_ip);
                g_traceroute->route_ip = NULL;
            }
        }
        else
        {
            char *string = concatenate_strings("%.3fms ", (float)latency);
            ft_putstr(&string);
            if (icmp_response->type == ICMP_DEST_UNREACH && icmp_response->code == 1)
                write(1, "!H ", 3);
            else
                write(1, " ", 1);
        }
        if (icmp_response->type == ICMP_DEST_UNREACH)
            if (state == 2 && ft_strncmp(g_traceroute->ip_addr, src, ft_strlen(g_traceroute->ip_addr)) == 0)
                exit(0);
    }
    return (0);
}
