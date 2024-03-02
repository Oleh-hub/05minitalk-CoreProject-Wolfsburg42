/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:16:48 by oruban            #+#    #+#             */
/*   Updated: 2024/02/27 18:37:46 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all   
https://medium.com/@leogaudin/minitalk-a-simple-client-server-communication-
system-57ccc2ae5178
https://github.com/rphlr/42-Evals 
https://github.com/jotavare/42-resources?tab=readme-ov-file#02-minitalk 
write() beacause it async-sygnal safe :
https://man7.org/linux/man-pages/man7/signal-safety.7.html
*/
#include "minitalk.h"
#include <unistd.h>
#include <limits.h>

/* function that is being executed as soon as signal defined by signal()
 comes */
void	ft_handler(int signal)
{
	static int	bit = 0;
	static char	byte = 0 ;

	if (signal == SIGUSR1)
		byte = byte | (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(STDOUT_FILENO, &byte, 1);
		bit = 0;
		byte = 0;
	}
}

int	main(void)
{
	pid_t	pid_int;
	char	*pid_str;

	pid_int = getpid();
	pid_str = ft_itoa(pid_int);
	write(STDOUT_FILENO, "server PID: ", 12);
	write(STDOUT_FILENO, pid_str, ft_strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
	free(pid_str);
	while (1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause();
	}
}
