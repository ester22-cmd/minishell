/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:05:37 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 21:05:37 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_content(t_mini *mini, char *key)
{
	t_nodenv	*node_env;

	node_env = mini->env->begin;
	while (node_env != NULL)
	{
		if (!ft_strcmp(node_env->key, key))
			return (ft_strdup(node_env->content));
		node_env = node_env->next;
	}
	return (NULL);
}

char *get_var(t_mini *mini, char *str, int i)
{
	char *var;
	char *content;
	int len;
	int j;

	len = 0;
	j = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	if (len > 0)
	{
		var = malloc(sizeof(char) * (len + 1));
		if (!var)
			return (NULL);
		i = 0;
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			var[i++] = str[j++];
		var[i] = '\0';
		content = get_var_content(mini, var);
		free(var);
		return (content ? content : ft_strdup(""));
	}
	return (ft_strdup(""));
}

char	*get_join(char *str)
{
	int		i;
	char	*aux;
	i = 0;
	if (str[i] == '$')
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	aux = ft_substr(str, 0, i - 1);
	return (aux);
}

char	*get_content(t_mini *mini, t_node *node, int i, int j)
{
	char	*content;

	content = NULL;
	if (node->str[i][j + 1] == '?')
		content = ft_itoa(g_return);
	else
		content = get_var(mini, node->str[i], j + 1);
	return (content);
}

char *transform(t_mini *mini, t_node *node, int i, int j)
{
	char *result = ft_strdup("");
	char *aux, *content;
	int var_len;

	while (node->str[i][j])
	{
		if (node->str[i][j] == '$' && (var_len = 0) == 0)
		{
			while (node->str[i][++j] && (ft_isalnum(node->str[i][j]) || node->str[i][j] == '_'))
				var_len++;
			if (var_len > 0 && (content = get_var_content(mini, ft_substr(node->str[i], j - var_len, var_len))))
			{
				aux = result;
				result = ft_strjoin(aux, content);
				free(aux);
				free(content);
			}
			else if (!var_len)
				result = ft_strjoin_free(result, "$");
		}
		else
			result = ft_strjoin_free(result, (char[]){node->str[i][j++], '\0'});
	}
	return (result);
}
