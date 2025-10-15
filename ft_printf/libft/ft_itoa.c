/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:01:23 by marlee            #+#    #+#             */
/*   Updated: 2025/06/18 18:07:30 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_of_digits(int nbr)
{
	int	count;

	if (nbr <= 0)
		count = 1;
	else
		count = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str_nbr;
	int		sign;
	int		len;
	long	n_long;

	n_long = n;
	if (n_long < 0)
		sign = -1;
	else
		sign = 1;
	len = number_of_digits(n_long);
	str_nbr = malloc(sizeof(char) * (len + 1));
	if (str_nbr == NULL)
		return (NULL);
	str_nbr[len] = '\0';
	while (len > 0)
	{
		str_nbr[--len] = sign * (n_long % 10) + '0';
		n_long = n_long / 10;
	}
	if (sign == -1)
		str_nbr[0] = '-';
	return (str_nbr);
}
