/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/15 20:01:40 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	sig_handler(int sig)
{
	static char		current_byte = 0;
	static int		bit_index = 0;

	if (sig == SIGUSR1)
		current_byte |= (0 << bit_index);
	else if (sig == SIGUSR2)
		current_byte |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		// printf("Received byte: %c (ASCII: %d)\n", current_byte, current_byte);
		if (current_byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_byte, 1);
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
