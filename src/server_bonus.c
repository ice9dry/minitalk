/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/20 23:14:31 by marlee           ###   ########.fr       */
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

static void	send_ack(t_client *client)
{
	if (client->pid != 0)
		kill(client->pid, SIGUSR1);
}

static void	reset_client(t_client *client, pid_t pid)
{
	client->pid = pid;
	client->bit_index = 0;
	client->char_index = 0;
	client->current_byte = 0;
}

void	handle_bit(int sig, siginfo_t *info, void *context)
{
	static t_client	client = {0, 0, 0, {0}, 0};
	
	(void)context;
	if (client.pid != info->si_pid)
		reset_client(&client, info->si_pid);
	if (sig == SIGUSR2)
		client.current_byte |= (1 << client.bit_index);
	client.bit_index++;
	if (client.bit_index == 8)
	{
		if (client.current_byte == '\0')
		{
			client.message[client.char_index] = '\0';
			write(1, client.message, client.char_index);
			write(1, "\n", 1);
			client.char_index = 0;
		}
		else if (client.char_index < 1023)
			client.message[client.char_index++] = client.current_byte;
		client.current_byte = 0;
		client.bit_index = 0;
	}
	send_ack(&client);
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
