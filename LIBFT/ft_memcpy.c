/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:45:32 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/04 20:31:19 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			x;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (src == NULL && dst == NULL)
		return (dst);
	x = 0;
	while (x < n)
	{
		d[x] = s[x];
		x++;
	}
	return (d);
}
