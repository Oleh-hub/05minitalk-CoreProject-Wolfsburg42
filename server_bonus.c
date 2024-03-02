/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:54:07 by oruban            #+#    #+#             */
/*   Updated: 2024/02/28 04:06:51 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <limits.h>

/* function that is being executed as soon as signal defined by signal()
 comes */
static void	ft_handler(int signal, siginfo_t *info, void *s)
{
	static int	bit = 0;
	static char	byte = 0 ;

	(void) s;
	if (signal == SIGUSR1)
		byte = byte | (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(STDOUT_FILENO, &byte, 1);
		if (byte == '\n')
		{
			usleep(100);
			kill(info->si_pid, SIGUSR2);
		}
		bit = 0;
		byte = 0;
	}
}

int	main(void)
{
	pid_t				pid_int;
	char				*pid_str;
	struct sigaction	sig;

	pid_int = getpid();
	pid_str = ft_itoa(pid_int);
	write(STDOUT_FILENO, "server PID: ", 12);
	write(STDOUT_FILENO, pid_str, ft_strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
	free(pid_str);
	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	while (1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
}
