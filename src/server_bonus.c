/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:21 by marlee            #+#    #+#             */
/*   Updated: 2025/10/18 16:55:47 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server_bonus.h"

volatile sig_atomic_t g_received_bit = -1;
volatile sig_atomic_t g_bit_ready = 0;

void sig_handler(int sig)
{
    // This handler does MINIMAL work - just record which signal arrived
    if (sig == SIGUSR1)
        g_received_bit = 0;
    else if (sig == SIGUSR2)
        g_received_bit = 1;

    g_bit_ready = 1;
}
void process_bits(void)
{
    static char message[1024];
    static int bit_index = 0;
    static int char_index = 0;
    static char current_byte = 0;

    while (1)
    {
        // Wait for a bit to be ready
        if (!g_bit_ready)
            continue;

        // Process the bit
        if (g_received_bit == 1)
            current_byte |= (1 << bit_index);
        // If bit is 0, we don't need to do anything (bit is already 0)

        bit_index++;
        g_bit_ready = 0;
        g_received_bit = -1;

        // Check if we have a complete byte
        if (bit_index == 8)
        {
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
        break; // Process one bit per loop iteration
    }
}
void	sig_handler_old(int sig)
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
	struct		sigaction sa;
	// sigset_t	block_mask;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);

	// sa.sa_mask = block_mask;
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	// signal(SIGUSR1, sig_handler);
	// signal(SIGUSR2, sig_handler);
	while (1)
	{
		pause();
		process_bits();
	}
	return (0);
}
