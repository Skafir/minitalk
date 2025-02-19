/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:56:09 by skafir            #+#    #+#             */
/*   Updated: 2025/02/19 08:45:30 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int		bit = 0;
	static char		character = 0;
	static pid_t	client_pid;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (signal == SIGUSR1)
		character |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (character == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(character, 1);
		bit = 0;
		character = 0;
	}
	kill(client_pid, SIGUSR1);
}

void	signal_(int signal, void *handler, int use_siginfo)
{
	struct sigaction	sa;

	if (use_siginfo)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signal, &sa, NULL) < 0)
	{
		ft_putstr_fd("Error : Sigaction\n", 1);
		exit(1);
	}
}

int	main(void)
{
	char	*client_pid;
	int		x;

	ft_putstr_fd("Server PID : ", 1);
	client_pid = ft_itoa(getpid());
	x = 0;
	while (client_pid[x])
	{
		ft_putchar_fd(client_pid[x], 1);
		x++;
	}
	ft_putchar_fd('\n', 1);
	signal_(SIGUSR1, handle_signal, 1);
	signal_(SIGUSR2, handle_signal, 1);
	while (1)
		pause();
	return (0);
}
