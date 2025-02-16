/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:43:51 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/03 19:59:01 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	c;

	c = n;
	if (c < 0)
	{
		c *= -1;
		ft_putchar_fd('-', fd);
	}
	if (c > 9)
		ft_putnbr_fd(c / 10, fd);
	ft_putchar_fd(c % 10 + '0', fd);
}
