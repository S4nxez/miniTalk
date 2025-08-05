/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:44:16 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/05 16:31:55 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server = BUSY;

void	ack_handler(void)
{
	g_server = READY;
}

void	send_char(char c, pid_t server)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0b10000000 >> bit))
			ft_kill(server, SIGUSR1);
		else
			ft_kill(server, SIGUSR2);
		bit++;
		if (bit == 8 && c == '\0')
			exit(EXIT_SUCCESS);
		while (g_server == BUSY)
			usleep(1);
		g_server = BUSY;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server;

	if (3 != argc)
	{
		ft_putstr_fd("Usage = ./client <PID> \"Message\"\n", 2);
		exit(EXIT_FAILURE);
	}
	server = ft_atoi(argv[1]);
	if (server == 0)
	{
		ft_putstr_fd("Invalid input, PID must be a number", 2);
		return (EXIT_FAILURE);
	}
	ft_signal(SIGUSR1, ack_handler, false);
	while (*argv[2])
		send_char(*argv[2]++, server);
	send_char('\0', server);
	return (EXIT_SUCCESS);
}
