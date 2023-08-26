#include "ft_traceroute.h"

t_traceroute	*g_traceroute;

/** @Brief Signal Handler
 * Handle the SIGKILL signal by setting the loop variable
 * to false. By doing so the program will quit the loop and
 * gives a report.
 * 
 * @param sig Interrupt Signal code
 * @return none
 */
void    interrupt_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_traceroute->routine_loop = 0;
        collect_memory();
        printf("\n");
        exit(0);
    }
    return ;
}

/**
 * @brief Initialize Ping Structure
 * Allocates memory for the global ping structure and initializes its fields.
 * The structure holds information related to ping operations, including IP address,
 * arguments, loop control, ICMP header, and destination address.
 *
 * @param None.
 * @return None.
 */
void    init_struct()
{
	g_traceroute = (t_traceroute *)malloc(sizeof(t_traceroute));
	if (g_traceroute == NULL)
        show_errors("ft_traceroute: can't allocate memory\n", EX_OSERR);
	g_traceroute->times = 0;
    g_traceroute->route_ip = NULL;
    g_traceroute->unreach = 0;
	return ;
}

/** @Brief Main function
 * Parsing arguments and execute the main program
 * 
 * @param argc Number of arguments
 * @param argv CL arguments
 * @return
 */
int     main(int argc, char **argv) 
{
    init_struct();
	 /* TO-DO: Parsing the command line arguments */
    parse_clo(argc, argv);
    // if (search_in_args(argc, argv))
    //     show_errors("", EX_HELP);
    if (getuid() != 0)
        show_errors("ft_traceroute: Lacking privilige for icmp socket.\n", EXIT_FAILURE);
    /* TO-DO: Handling signales */
    signal(SIGINT, (void *)&interrupt_handler);
    /* TO-DO: sends icmp echo packets to targeted host */
    traceroute_start();
    return (0);
}