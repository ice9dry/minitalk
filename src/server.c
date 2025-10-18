/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/18 11:57:17 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	sig_handler(int sig)
{
	static char		message[1024];
	static int		bit_index = 0;
	static int		char_index = 0;
	static char		current_byte = 0;

	// if (sig == SIGUSR1)
	// 	current_byte |= (0 << bit_index);
	// else
	
	if (sig == SIGUSR2)
		current_byte |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		// printf("Received byte: %c (ASCII: %d)\n", current_byte, current_byte);
		if (current_byte == '\0')
		{
			if (char_index > 0)
			{
				message[char_index] = '\0';
				write(1, message, char_index);
				write(1, "\n", 1);
			}
			char_index = 0;
		}
		else
		{
			if (char_index < 1023)
			{
				message[char_index] = current_byte;
				char_index++;
			}
		}
		bit_index = 0;
		current_byte = 0;
	}
	// ft_printf("Signal received!\n");
}

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
