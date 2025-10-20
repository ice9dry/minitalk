/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/20 22:51:10 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_client_pid = 0;

void	send_ack(void)
{
	if (g_client_pid != 0)
		kill(g_client_pid, SIGUSR1);
}

void	sig_handler(int sig)
{
	static char		message[1024];
	static int		bit_index = 0;
	static int		char_index = 0;
	static char		current_byte = 0;

	if (sig == SIGUSR2)
		current_byte |= (1 << bit_index);
	bit_index++;
	if (bit_index != 8)
		return (send_ack());
	if (current_byte == '\0')
	{
		message[char_index] = '\0';
		write(1, message, char_index);
		write(1, "\n", 1);
		char_index = 0;
	}
	else if (char_index < 1023)
		message[char_index++] = current_byte;
	bit_index = 0;
	current_byte = 0;
	send_ack();
}

	// Removed below as it serves no purpose other than consistency
	// if (sig == SIGUSR1)
	// 	current_byte |= (0 << bit_index);

int	main()
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
	{
		pause();
	}
	return (0);
}
