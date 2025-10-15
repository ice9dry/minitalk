/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:59:33 by marlee            #+#    #+#             */
/*   Updated: 2025/07/02 15:30:19 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
	count++;
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned(n / 10);
	ft_putchar((n % 10) + '0');
	count++;
	return (count);
}

int	ft_putnbr_base(unsigned long n, char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
		count = ft_putnbr_base(n / 16, base);
	write(1, &base[n % 16], 1);
	count++;
	return (count);
}
