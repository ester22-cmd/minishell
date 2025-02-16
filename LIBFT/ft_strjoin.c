/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:42:51 by amaferre          #+#    #+#             */
/*   Updated: 2024/10/26 22:47:17 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	sub1;
	size_t	sub2;

	sub1 = ft_strlen(s1);
	sub2 = ft_strlen(s2);
	str = malloc((sub1 + sub2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, sub1 + 1);
	ft_strlcpy(&str[sub1], s2, sub2 + 1);
	return (str);
}
