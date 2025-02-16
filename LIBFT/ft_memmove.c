/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:52:26 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/04 20:30:57 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!src && !dst)
		return (NULL);
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	else
	{
		while (n > 0)
		{
			n--;
			*(unsigned char *)(dst + n) = *(unsigned char *)(src + n);
		}
	}
	return (dst);
}
