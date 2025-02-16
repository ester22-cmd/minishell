/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:33:55 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/04 21:13:32 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		x;
	void	*y;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(0));
	}
	x = nmemb * size;
	if (x / nmemb != size)
		return (malloc(0));
	y = malloc(x);
	if (y == NULL)
		return (NULL);
	else
		ft_bzero(y, x);
	return (y);
}
