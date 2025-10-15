/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:09:29 by marlee            #+#    #+#             */
/*   Updated: 2025/06/18 18:09:35 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*strjoin;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (strjoin == NULL)
		return (NULL);
	strjoin[s1_len + s2_len] = '\0';
	while (s2_len--)
		strjoin[s2_len + s1_len] = s2[s2_len];
	while (s1_len--)
		strjoin[s1_len] = s1[s1_len];
	return (strjoin);
}
