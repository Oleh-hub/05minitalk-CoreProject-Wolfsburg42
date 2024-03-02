/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:57:33 by oruban            #+#    #+#             */
/*   Updated: 2024/02/27 18:29:14 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_bits(int pid, char byte)
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
	}
	else
	{
		write(STDOUT_FILENO, "Error: wrong format.\n", 21);
		write(STDOUT_FILENO, "Format: ./client <PID> <MESSAGE>\n", 33);
		return (1);
	}
	return (0);
}
