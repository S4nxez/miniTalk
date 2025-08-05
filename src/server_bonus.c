/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:44:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/05 16:45:59 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signal, siginfo_t *info, void *more_info)
{
	static pid_t	client;
	static char		c;
	static int		bit_len;

	(void)more_info;
	client = info->si_pid;
	if (SIGUSR1 == signal)
		c |= (0b10000000 >> bit_len);
	else if (SIGUSR2 == signal)
		c &= ~(0b10000000 >> bit_len);
	bit_len++;
	if (CHAR_BIT == bit_len)
	{
		bit_len = 0;
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			ft_kill(client, SIGUSR2);
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
	}
	ft_kill(client, SIGUSR1);
}

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	ft_signal(SIGUSR1, handler, true);
	ft_signal(SIGUSR2, handler, true);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
