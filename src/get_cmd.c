/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:15:51 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 23:15:51 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void check_dollar(t_mini *mini, t_node *node)
{
	int i;
	int j;

	i = -1;
	while (node->str[++i])
	{
		j = -1;
		while (node->str[i][++j])
		{
			is_in_quote(node->str[i][j], mini);
			if (!mini->is_open_s && node->str[i][j] == '$' && node->str[i][j + 1] != ' ' && node->str[i][j + 1] != '\0')
			{
				expand_var(mini, node, i);
				break;
			}
		}
	}
}

char *dirty_jobs(char *str)
{
	char *result;
	int j;
	int k;

	result = malloc(ft_strlen(str) + 1);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (str[j] != D_QUOTE && str[j] != S_QUOTE) // Ignora aspas
			result[k++] = str[j];
		j++;
	}
	result[k] = '\0';
	return (result);
}

char **remove_quotes(char **str, int len)
{
	char **aux;
	int i;
	int k;

	aux = malloc(sizeof(char *) * (len + 1));
	i = -1;
	k = 0;
	while (str[++i])
	{
		aux[k++] = dirty_jobs(str[i]);
	}
	aux[k] = NULL;
	return (aux);
}

void get_cmd(t_mini *mini, t_node *node)
{
	char **aux;
	char **holder;
	int i;
	int j;

	i = -1;
	j = 0;
	aux = malloc(sizeof(char *) * (len_node(mini, node->str) + 1));
	node->str[0] = dirty_jobs(node->str[0]);

	while (node->str[++i])
	{
		if (node->str[i][0] == '<' || node->str[i][0] == '>')
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i]);
	}
	aux[j] = NULL;
	holder = remove_quotes(aux, len_node(mini, aux));
	minifree(node->str);
	holder = remove_quotes(aux, len_node(mini, aux));
	minifree(aux);
	node->str = holder;
	check_dollar(mini, node);
}

void get_cmd_builtin(t_mini *mini, t_node *node)
{
	char **aux;
	int i;
	int j;
	int len;

	i = 0;
	len = len_node(mini, node->str);
	aux = malloc(sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i])
	{
		is_in_quote_str(node->str[i], mini, 0);
		if ((!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], ">") || !ft_strcmp(node->str[i], "<<") || !ft_strcmp(node->str[i], ">>")) && mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]);
	}
	aux[j] = NULL;
	minifree(node->str);
	node->str = aux;
	check_dollar(mini, node);
}
