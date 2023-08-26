#include "ft_utils.h"

/** @brief Help function
 * Printing the usage of ft_traceroute
 * to the Stdout
 *
 * @param void
 * @return none
 */
 void   show_usage( void )
{
     printf("Try './ft_traceroute -?' or './ft_traceroute --help' for more information.\n");
     return ;
}

void    show_help()
{
    printf("Usage:\n");
    printf("  ft_traceroute [options] <destination>\n\n");
    printf("Options:\n");
    printf("  -f <ttl>           Set the starting time-to-live (TTL) value.\n");
    printf("  -m <max_ttl>       Set the maximum number of hops (TTL).\n");
    printf("  -w <timeout>       Set the timeout for waiting for a response in seconds.\n");
    printf("  -?                 Display help and usage information.\n");
    printf("  -t <tos>           Set the Type of Service (ToS) value.\n");
    printf("  -p <port>          Specify the destination port number.\n\n");
    printf("<destination>        Replace with the DNS name or IP address of the target.\n");

    return ;
}