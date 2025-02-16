/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:45:42 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/04 22:09:35 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	word_len;
	size_t	word_count;

	word_len = 0;
	word_count = 0;
	if (s[0] != c && s[0] != '\0')
		word_count++;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1) != '\0')
			word_count++;
		s++;
	}
	return (word_count);
}

static char	*ft_alloc_word(char const *s, char c)
{
	size_t	length;
	char	*new_string;

	length = 0;
	while (s[length] && s[length] != c)
	{
		length++;
	}
	new_string = (char *)malloc(sizeof (char) * (length + 1));
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s, length + 1);
	return (new_string);
}

static void	ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	ft_load(char **split, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			split[i] = ft_alloc_word(s, c);
			if (!split[i])
			{
				ft_free(split);
				return (0);
			}
			i++;
			while (*s != '\0' && *s != c)
			{
				s++;
			}
		}
		else
			s++;
	}
	split[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**split_result;

	count = ft_count_word(s, c);
	split_result = (char **)malloc((count + 1) * sizeof(char *));
	if (!split_result)
		return (NULL);
	if (!ft_load(split_result, s, c))
		return (NULL);
	return (split_result);
}
