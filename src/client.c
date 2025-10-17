/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/17 15:43:31 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
		usleep(50);
		i++;
	}
}

void	send_string(int server_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(server_pid, str[i]);
		i++;
	}
	send_char(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	int		server_pid;
	if (argc != 3)
	{
		ft_printf("Usage: ./client_bit [PID] [message]\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	send_string(server_pid, argv[2]);
	// send_char(server_pid, '\n');
	// kill (server_pid, SIGUSR1);
	return (0);
}
