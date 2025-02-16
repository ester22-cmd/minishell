/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:32 by amaferre          #+#    #+#             */
/*   Updated: 2024/10/22 20:22:27 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *large, const char *small, size_t len)
{
	size_t	x;
	size_t	small_len;

	x = 0;
	small_len = ft_strlen(small);
	if (small_len == 0)
		return ((char *)large);
	while (*large && x <= len)
	{
		if (len - x++ >= small_len && !ft_strncmp(large, small, small_len))
			return ((char *)large);
		large++;
	}
	return (0);
}
