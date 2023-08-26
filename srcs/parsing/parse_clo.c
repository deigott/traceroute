#include "ft_traceroute.h"
#include "ft_libft.h"
/** @Brief Init Args
 * Initialize args struct
 *
 * @param none
 * @return t_args*
 */
t_args  *init_args( void )
{
    t_args *args;

    args = (t_args *) malloc(sizeof(t_args) * 1);
    if (args == NULL)
        return (args);
    args->invalid_option = 0;
    args->hostname = NULL;
    args->options = 0;
    args->ttl = TRACE_TTL;
    args->timeout = 3;
    args->max_hop = MAX_HOPS;
    args->tos = 4;
    args->port = PORT;
    args->count_valid = 0;
    return (args);
}

size_t traceroute_cvt_number (const char *optarg, size_t maxval, int allow_zero)
{
  char *p;
  unsigned long int n;

  n = strtoul (optarg, &p, 0);
  if (*p)
    show_errors(concatenate_strings("ft_traceroute: invalid value (`%s' near `%s')\n", optarg, p),EXIT_FAILURE);

  if (n == 0 && !allow_zero)
    show_errors(concatenate_strings("ft_traceroute: option value too small: %s\n", optarg) ,EXIT_FAILURE);

  if (maxval && n > maxval)
    show_errors(concatenate_strings("ft_traceroute: option value too big: %s\n", optarg) ,EXIT_FAILURE);

  return n;
}

/**
 * @brief Parsing command line
 * parse command line argumments 
 * and store valid arguments in t_args struct
 */
void    parse_clo(int len, char *clo_args[])
{
    int i;
    char *p;

    p = NULL;
    i = 1;
    g_traceroute->args = init_args();
    if (g_traceroute->args == NULL)
        show_errors("ft_traceroute: can't allocate memory\n", EX_OSERR);
    // TO-DO: Parsing only valid options and break if any invalid_option appears
    while (i < len)
    {
        if (ft_strncmp(clo_args[i], "-?", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--help", ft_strlen(clo_args[i])) == 0)
            g_traceroute->args->options |= OPT_HELP;
        else if (ft_strncmp(clo_args[i], "-f", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--first_hop", ft_strlen(clo_args[i])) == 0)
        {
            g_traceroute->args->options |= OPT_TTL;
            if (!clo_args[i + 1])
                show_errors("ft_traceroute: option requires an argument -- 'f'\n", EX_USAGE);
            g_traceroute->args->ttl = strtol (clo_args[i + 1], &p, 0);
            if (*p || g_traceroute->args->ttl <= 0 || g_traceroute->args->ttl > 255)
                show_errors(concatenate_strings("ft_traceroute: impossible distance `%s'\n", clo_args[i + 1]), EXIT_FAILURE);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-w", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--deadline", ft_strlen(clo_args[i])) == 0)
        {
            g_traceroute->args->options |= OPT_TIMEOUT;
            if (!clo_args[i + 1])
                show_errors("ft_traceroute: option requires an argument -- 'w'\n", EX_USAGE);
            g_traceroute->args->timeout = strtol (clo_args[i + 1], &p, 0);
            if (*p || g_traceroute->args->timeout < 0 || g_traceroute->args->timeout > 60)
                show_errors(concatenate_strings("ft_traceroute: ridiculous waiting time `%s'\n", clo_args[i + 1]), EXIT_FAILURE);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-p", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--port", ft_strlen(clo_args[i])) == 0)
        {
            if (!clo_args[i + 1])
                show_errors("ft_traceroute: option requires an argument -- 'p'\n", EX_USAGE);
            g_traceroute->args->port = strtol (clo_args[i + 1], &p, 0);
            if (*p || g_traceroute->args->port <= 0 || g_traceroute->args->port > 65536)
                show_errors(concatenate_strings("ft_traceroute: invalid port number `%s'\n", clo_args[i + 1]), EXIT_FAILURE);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-t", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--tos", ft_strlen(clo_args[i])) == 0)
        {
            g_traceroute->args->options |= OPT_TOS;
            if (!clo_args[i + 1])
                show_errors("ft_traceroute: option requires an argument -- 't'\n", EX_USAGE);
            g_traceroute->args->tos = strtol (clo_args[i + 1], &p, 0);
            if (*p || g_traceroute->args->tos < 0 || g_traceroute->args->tos > 255)
                show_errors(concatenate_strings("ft_traceroute: invalid TOS value `%s'\n", clo_args[i + 1]), EXIT_FAILURE);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-m", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--max-hop", ft_strlen(clo_args[i])) == 0)
        {
            if (!clo_args[i + 1])
                show_errors("ft_traceroute: option requires an argument -- 'm'\n", EX_USAGE);
            g_traceroute->args->max_hop = strtol(clo_args[i + 1], &p, 0);
            if (*p || g_traceroute->args->max_hop <= 0 || g_traceroute->args->max_hop > 255)
                show_errors(concatenate_strings("ft_traceroute: invalid hops value `%s'\n", clo_args[i + 1]), EXIT_FAILURE);
            i++;
        }
        else if (clo_args[i][0] != '-' && !g_traceroute->args->hostname)
            g_traceroute->args->hostname = ft_strdup(clo_args[i]);
        else if (clo_args[i][0] == '-')
            show_errors(concatenate_strings("ft_traceroute: invalid option -- %s\n", &clo_args[i][1]), EX_USAGE);
        i++;
    }
    if (g_traceroute->args->options & OPT_HELP)
        show_errors("", EX_HELP);
    if (!g_traceroute->args->hostname)
        show_errors("ft_traceroute: missing host operand\n", EX_USAGE);
}