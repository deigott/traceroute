# Color codes for better output
COLOR_RESET=\033[0m
COLOR_RED=\033[31m
COLOR_GREEN=\033[32m
COLOR_YELLOW=\033[33m
COLOR_BLUE=\033[34m

# Compilation flags and variables
FLAGS=-Wall -Werror -Wextra -fsanitize=address -g
CC=gcc
EXEC_NAME=ft_traceroute
SRCS=srcs/main.c srcs/traceroute.c srcs/libft/ft_strdup.c srcs/socket/checksum.c srcs/socket/construct_icmp_packet.c srcs/socket/create_socket.c srcs/libft/ft_putstr.c srcs/socket/receive.c srcs/socket/send.c srcs/libft/ft_strncmp.c srcs/libft/ft_bzero.c srcs/libft/ft_memcpy.c srcs/libft/ft_strlen.c srcs/libft/ft_strstr.c srcs/utils/collect_memory.c srcs/utils/concatenate_strings.c srcs/utils/show_help.c srcs/utils/show_errors.c srcs/parsing/parse_clo.c 
INCLUDES=includes/
IP_ADDRESS := $(shell ip addr | grep "enp1s0" | grep inet | cut -d ' ' -f6 | cut -d '/' -f1)
IP := $(echo "HEHLLO")

all: $(EXEC_NAME)

$(EXEC_NAME): $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -D SRC_ADDRESS=\"$(IP_ADDRESS)\" -I $(INCLUDES) -o $(EXEC_NAME)
	@echo "$(COLOR_BLUE)$(EXEC_NAME) executable created$(COLOR_RESET)"

clean:
	@rm -rf $(EXEC_NAME)
	@echo "$(COLOR_YELLOW)Cleaned up the generated files$(COLOR_RESET)"

fclean: clean

re: fclean all

.PHONY: all clean fclean re