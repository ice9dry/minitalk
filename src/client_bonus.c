/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/21 19:19:28 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client_bonus.h"

volatile sig_atomic_t	g_flag;

void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_flag = 1;
}

void	send_char(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_flag = 0;
		if ((c >> bit) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		while (g_flag != 1)
			pause();
		bit++;
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

int	is_valid_pid(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [message]\n");
		return (1);
	}
	if (!is_valid_pid(argv[1]))
	{
		ft_printf("Error: PID must contain only digits (0-9).\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
	{
		ft_printf("Error: Invalid PID.\n");
		return (1);
	}
	signal(SIGUSR1, ack_handler);
	send_string(server_pid, argv[2]);
	ft_printf("Message sent successfully!\n");
	return (0);
}
