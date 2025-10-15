/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:43:19 by marlee            #+#    #+#             */
/*   Updated: 2025/10/09 21:26:22 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	handle_fraction(const char *str)
{
	double	fraction;
	double	power;

	fraction = 0.0;
	power = 1.0;
	while (*str >= '0' && *str <= '9')
	{
		fraction = fraction * 10.0 + (*str - '0');
		power *= 10.0;
		str++;
	}
	return (fraction / power);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	result = ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		result += handle_fraction(str + 1);
	return (result * sign);
}
