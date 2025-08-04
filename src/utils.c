/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:44:46 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/04 19:10:37 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_signal(int signal, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
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
		ft_putstr_fd("Sigaction failed", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_kill(pid_t pid, int signal)
{
	if (pid < 0)
		ft_putstr_fd("Error. The PID must be greater than 0", 2);
	if (kill(pid, signal) < 0)
	{
		ft_putstr_fd("ft_kill failed", 2);
		exit(EXIT_FAILURE);
	}
}
