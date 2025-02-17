/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalahaye <jalahaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:56:09 by skafir            #+#    #+#             */
/*   Updated: 2025/02/17 14:15:14 by jalahaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

char	*malzero(int len)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		free(res);
		return (NULL);
	}
	res[0] = '0';
	return (res);
}

int	int_len(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*result;
	long	nbr;

	nbr = n;
	len = int_len(nbr);
	result = malzero(len);
	if (!result)
		return (NULL);
	if (nbr < 0)
		nbr = -nbr;
	i = len - 1;
	while (nbr != 0)
	{
		result[i] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	result[len] = 0;
	return (result);
}

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
			write(1, "\n", 1);
		else
			write(1, &character, 1);
		bit = 0;
		character = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	char				*client_pid;
	int					x;

	write(1, "Server PID : ", 13);
	client_pid = ft_itoa(getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	while (*client_pid)
		write(1, client_pid++, 1);
	free(client_pid);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
