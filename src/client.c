/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:44:16 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/02 14:02:10 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server = BUSY;

void	end_handler(void)
{
	write(STDOUT_FILENO, "200\n", 4);
	exit(EXIT_SUCCESS);
}

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
		while (g_server == BUSY)
			usleep(42);
		g_server = BUSY;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server;
	char	*message;

	if (3 != argc)
	{
		fputs("Usage = ./client <PID> \"Message\"\n", stderr);
		exit(EXIT_FAILURE);
	}
	server = atoi(argv[1]);
	message = argv[2];
	ft_signal(SIGUSR1, ack_handler, false);
	ft_signal(SIGUSR2, end_handler, false);
	while (*message)
		send_char(*message++, server);
	send_char('\0', server);
	return (EXIT_SUCCESS);
}
