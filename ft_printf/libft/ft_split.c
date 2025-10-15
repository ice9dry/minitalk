/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlee <marlee@student.42student.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:05:57 by marlee            #+#    #+#             */
/*   Updated: 2025/06/18 18:09:17 by marlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **result, int word_index)
{
	while (word_index--)
		free(result[word_index]);
	free(result);
	return (NULL);
}

static int	skip_delimiters(char const *s, char c, int start)
{
	while (s[start] == c)
		start++;
	return (start);
}

static int	count_length(char const *s, char c, int start, int len)
{
	while (s[start + len] != c && s[start + len])
		len++;
	return (len);
}

static int	ft_count_words(char const *s, char c)
{
	int		count;
	char	prev_letter;

	prev_letter = c;
	count = 0;
	while (*s)
	{
		if (*s != c && prev_letter == c)
			count++;
		prev_letter = *s;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		start;
	int		word_index;
	int		len;

	start = 0;
	result = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (result == NULL)
		return (NULL);
	word_index = 0;
	while (s[start])
	{
		start = skip_delimiters(s, c, start);
		if (s[start] == '\0')
			break ;
		len = 0;
		len = count_length(s, c, start, len);
		result[word_index] = ft_substr(s, start, len);
		if (result[word_index] == NULL)
			return (free_all(result, word_index));
		start = start + len;
		word_index++;
	}
	result[word_index] = NULL;
	return (result);
}
