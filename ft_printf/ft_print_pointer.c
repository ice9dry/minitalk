/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:04:34 by marlee            #+#    #+#             */
/*   Updated: 2025/06/26 17:18:03 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(void *ptr)
{
	int				count;
	unsigned long	address;
	char			*base;

	address = (unsigned long)ptr;
	base = "0123456789abcdef";
	if (address == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = ft_putnbr_base(address, base);
	return (2 + count);
}
