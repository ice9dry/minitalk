/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:39:31 by marlee            #+#    #+#             */
/*   Updated: 2025/05/26 18:26:59 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndle, size_t len)
{
	size_t	hay_len;
	size_t	i;
	size_t	j;

	if (ndle[0] == '\0')
		return ((char *)&hay[0]);
	hay_len = 0;
	hay_len = ft_strlen(hay);
	if (hay_len > len)
		hay_len = len;
	i = 0;
	while (i < hay_len)
	{
		if (hay[i] == ndle[0])
		{
			j = 0;
			while (ndle[j] != '\0' && i + j < hay_len && hay[i + j] == ndle[j])
				j++;
			if (ndle[j] == '\0')
				return ((char *)&hay[i]);
		}
		i++;
	}
	return (NULL);
}
