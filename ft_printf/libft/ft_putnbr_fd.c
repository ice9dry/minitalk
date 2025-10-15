/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:28:06 by marlee            #+#    #+#             */
/*   Updated: 2025/06/18 18:08:56 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	str[11];
	int		i;
	long	n_long;

	i = 0;
	n_long = n;
	if (n_long == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n_long < 0)
	{
		write(fd, "-", 1);
		n_long = -n_long;
	}
	while (n_long > 0)
	{
		str[i++] = (n_long % 10) + '0';
		n_long /= 10;
	}
	while (--i >= 0)
	{
		write(fd, &str[i], 1);
	}
}
