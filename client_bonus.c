/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:51:24 by skafir            #+#    #+#             */
/*   Updated: 2025/02/19 08:45:57 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"

volatile sig_atomic_t	g_confirmed = 0;

void	confirmation_handler(int signal)
{
	(void)signal;
	g_confirmed = 1;
}

void	send_character(pid_t server_pid, char character)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_confirmed = 0;
		if (character & (1 << (7 - bit)))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		++bit;
		while (!g_confirmed)
			pause();
	}
}

void	send_message(pid_t server_pid, char *message)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = confirmation_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	while (*message)
		send_character(server_pid, *message++);
	send_character(server_pid, '\0');
	exit(0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3)
	{
		ft_putstr_fd("Usage : ./client [server_pid] [message]\n", 1);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 0)
		return (1);
	message = argv[2];
	send_message(server_pid, message);
	return (0);
}
