/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:49:19 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/01 17:11:38 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	x;

	x = 0;
	str = (char *)s;
	while (x < n)
	{
		if ((unsigned char)str[x] == (unsigned char)c)
			return ((char *)s + x);
		x++;
	}
	return (NULL);
}
