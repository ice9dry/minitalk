/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/18 23:18:48 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server_bonus.h"

typedef struct s_client
{
	pid_t	pid;
	int		bit_index;
	char	current_byte;
	char	message[1024];
	int		char_index;
}	t_client;

t_client g_client = {0, 0, 0, {0}, 0};

void	handle_bit(int sig, siginfo_t *info, void *context)
{
	(void)context;

	// Initialize client PID if new client
	if (g_client.pid != info->si_pid)
	{
		g_client.pid = info->si_pid;
		g_client.bit_index = 0;
		g_client.char_index = 0;
		g_client.current_byte = 0;
	}

	// Set the bit
	if (sig == SIGUSR2)
		g_client.current_byte |= (1 << g_client.bit_index);
	g_client.bit_index++;

	// If byte complete
	if (g_client.bit_index == 8)
	{
		if (g_client.current_byte == '\0')
		{
			// End of message, print and reset
			write(1, g_client.message, g_client.char_index);
			write(1, "\n", 1);
			g_client.char_index = 0;
		}
		else
		{
			if (g_client.char_index < 1023)
				g_client.message[g_client.char_index++] = g_client.current_byte;
		}
		g_client.current_byte = 0;
		g_client.bit_index = 0;
	}

	// Send ACK to client
	kill(g_client.pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction sa;

	ft_printf("Bonus Server PID: %d\n", getpid());

	sa.sa_sigaction = handle_bit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}
