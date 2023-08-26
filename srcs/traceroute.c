#include "ft_traceroute.h"

void        fqdn_info()
{
    // Set up the destination address
    memset(&g_traceroute->dest_addr, 0, sizeof(g_traceroute->dest_addr));
    g_traceroute->dest_addr.sin_family = AF_INET;
    g_traceroute->dest_addr.sin_port = htons(g_traceroute->args->port); // Traceroute typically uses this port

    // Set up hints for getaddrinfo()
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;

    int status = getaddrinfo(g_traceroute->args->hostname, NULL, &hints, &result);
    if (status != 0)
        show_errors("ft_traceroute: unknown host\n", EXIT_FAILURE);
    char buffer[INET_ADDRSTRLEN];
    struct sockaddr_in *dest = (struct sockaddr_in *)result->ai_addr;
    inet_ntop(AF_INET, &(dest->sin_addr), buffer, INET_ADDRSTRLEN);
    inet_pton(AF_INET, buffer, &(g_traceroute->dest_addr.sin_addr));
    g_traceroute->ip_addr = ft_strdup(buffer);
    freeaddrinfo(result);
    return ;
}

void        traceroute_start()
{
    char *string;
    fqdn_info();
    create_socket();
    string = concatenate_strings("traceroute to %s (%s), %d hops max\n", g_traceroute->args->hostname,g_traceroute->ip_addr, g_traceroute->args->max_hop);
    ft_putstr(&string);
    for (int ttl = g_traceroute->args->ttl; ttl <= g_traceroute->args->max_hop; ++ttl) {
        char *string = concatenate_strings(" %2d   ", ttl);
        ft_putstr(&string);
        for (int i = 0;i<3;i++)
        {
            // Set the TTL for the socket
            if (setsockopt(g_traceroute->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
                show_errors("ft_traceroute: setsocketopt error!\n", EXIT_FAILURE);
            send_icmp_packet();
            // Sleep a bit before sending the next packet
            if (recv_icmp_packet(i) == 1 && g_traceroute->args->timeout != 0)
                usleep(10000 * 100);
        }
        if (g_traceroute->route_ip)
        {
            free(g_traceroute->route_ip);
            g_traceroute->route_ip = NULL;
        }
        if (g_traceroute->unreach)
            exit(0);
    }

    return ;
}