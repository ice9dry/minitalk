/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/15 19:50:04 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	send_char(int server_pid, char c)
{
	int		i;
	int		bit;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		i++;
	}
}
int	main(int argc, char **argv)
{
	int		server_pid;
	if (argc != 2)
	{
		ft_printf("Usage: ./client_bit [PID]\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	send_char(server_pid, 'A');
	send_char(server_pid, '\n');
	// kill (server_pid, SIGUSR1);
	return (0);
}
