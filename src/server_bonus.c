/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/21 19:07:15 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server_bonus.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int		bit_index = 0;
	static char		current_char = 0;
	pid_t			client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (sig == SIGUSR2)
		current_char |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		kill(client_pid, SIGUSR1);
		current_char = 0;
		bit_index = 0;
	}
	else
		kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Bonus Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
