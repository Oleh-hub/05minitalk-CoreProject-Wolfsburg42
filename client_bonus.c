/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:52:52 by oruban            #+#    #+#             */
/*   Updated: 2024/02/28 04:08:55 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* The function that 
The server acknowledges every message received by sending back a signal to the
client 
where ft_handler defined bz signal() as:
void (*signal(int sig, void (*func)(int)))(int);
*/
static void	ft_handler(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "Message received by server_bonus.\n", 34);
	exit(0);
}

static void	ft_send_bits(int pid, char byte)
{
	int		j;

	j = 0;
	while (j < 8)
	{
		if (1 << j & byte)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		j++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		i = -1;
		while (av[2][++i])
			ft_send_bits(pid, av[2][i]);
		ft_send_bits(pid, '\n');
		while (1)
		{
			signal(SIGUSR1, ft_handler);
			signal(SIGUSR2, ft_handler);
			pause();
		}
	}
	else
	{
		write(STDOUT_FILENO, "Error: wrong format.\n", 21);
		write(STDOUT_FILENO, "Format: ./client <PID> <MESSAGE>\n", 33);
		return (1);
	}
	return (0);
}
