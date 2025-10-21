/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/21 16:46:03 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	sig_handler(int sig)
{
	static int		bit_index = 0;
	static char		current_byte = 0;

	if (sig == SIGUSR2)
		current_byte |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_byte, 1);
		bit_index = 0;
		current_byte = 0;
	}
}

	// Removed below as it serves no purpose other than consistency
	// if (sig == SIGUSR1)
	// 	current_byte |= (0 << bit_index);

int	main(void)
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
