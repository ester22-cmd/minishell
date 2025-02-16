/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:06:23 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 21:06:23 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_var(t_mini *mini, t_node *node, int i)
{
	char		*holder;

	holder = transform(mini, node, i, 0);
	if (holder != NULL)
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(holder);
		free(holder);
	}
	else
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(" ");
	}
}
