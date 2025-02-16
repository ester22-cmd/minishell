/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:43:43 by amaferre          #+#    #+#             */
/*   Updated: 2024/10/22 20:20:25 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	dst_len;
	size_t	src_len;

	x = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	while (src[x] && (dst_len + 1) < size)
	{
		dst[dst_len++] = src[x++];
	}
	dst[dst_len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[x]));
}
