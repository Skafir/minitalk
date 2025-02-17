/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:51:24 by skafir            #+#    #+#             */
/*   Updated: 2025/02/17 13:55:53 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_confirmed = 0;

int	ft_atoi(const char *nptr)
{
	int	x;
	int	sign;
	int	result;

	x = 0;
	sign = 1;
	result = 0;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == ' ')
		nptr++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x] == '-')
			sign *= -1;
		x++;
	}
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		result = result * 10 + (nptr[x] - 48);
		nptr++;
	}
	return (result * sign);
}

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
	int					i;

	sa.sa_flags = 0;
	sa.sa_handler = confirmation_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	while (message[i] != '\0')
	{
		send_character(server_pid, message[i]);
		i++;
	}
	send_character(server_pid, '\0');
	write(1, "Message envoye avec succes !\n", 29);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3)
	{
		write(2, "Usage : ./client [server_pid] [message]\n", 40);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 0)
		return (1);
	message = argv[2];
	send_message(server_pid, message);
	return (0);
}
