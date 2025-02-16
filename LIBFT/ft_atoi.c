/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:03:24 by amaferre          #+#    #+#             */
/*   Updated: 2024/11/01 17:06:18 by amaferre         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

static int	isnegative(char *str, int *i)
{
	int	count;
	int	sign;

	count = 0;
	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		count++;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		i;
	int		sign;
	int		result;

	i = 0;
	str = (char *)nptr;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	sign = isnegative(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
