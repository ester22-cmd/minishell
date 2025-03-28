/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniunset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:18:36 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 23:18:36 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	miniunset(t_env *env, t_node *node, t_nodenv *aux, t_nodenv *prev)
{
	while (aux != NULL && node->str[1])
	{
		if (ft_strcmp(aux->key, node->str[1]))
		{
			if (aux == env->begin && prev == env->begin)
				aux = aux->next;
			else
			{
				aux = aux->next;
				prev = prev->next;
			}
		}
		else
		{
			prev->next = aux->next;
			free(aux->key);
			free(aux->content);
			free(aux);
			aux = prev->next;
			break ;
		}
	}
	g_return = 0;
}
