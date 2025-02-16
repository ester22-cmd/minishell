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

void	check_dollar(t_mini *mini, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->str[i]) 
	{
		j = 0;
		while (node->str[i][j])
		{
			is_in_quote(node->str[i][j], mini);
			if (mini->is_open_s == 0 && node->str[i][j] == '$'
				&& node->str[i][j + 1] != ' ' && node->str[i][j + 1] != '\0')
			{
				expand_var(mini, node, i);
				break ;
			}
			j++;
		}
		i++;
	}
}

char	*dirty_jobs(char **str, int i)
{
	char	*holder;
	char	*aux;
	int		start;
	int		end;
	int		j;

	j = 0;
	holder = ft_strdup(str[i]);
	while (holder[j] && holder[j] == ' ') 
		j++;
	while (holder[j] && (holder[j] == D_QUOTE || holder[j] == S_QUOTE))
		j++;
	start = j;
	while (holder[j] && holder[j] != D_QUOTE && holder[j] != S_QUOTE)
		j++;

	end = j - 1;
	aux = ft_substr(holder, start, end - start + 1);
	return (aux);
}

char	**remove_quotes(char **str, int len, int i, int k)
{
	char	**aux;

	aux = malloc(sizeof(char *) * len + 1);
	while (str[i])
	{
		if (is_just_quote(str[i]))
		{
			aux[k] = dirty_jobs(str, i);
			k++;
		}
		i++;
	}
	aux[k] = NULL;
	return (aux);
}

void	get_cmd(t_mini *mini, t_node *node)
{
	char	**aux;
	char	**holder;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = len_node(mini, node->str);
	aux = malloc(sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i])
	{
		if (node->str[i][0] == '<' || node->str[i][0] == '>')
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]);
	}
	aux[j] = NULL;
	len = len_node(mini, aux);
	holder = remove_quotes(aux, len, 0, 0);
	minifree(node->str);
	minifree(aux);
	node->str = holder;
	check_dollar(mini, node);
}

void	get_cmd_builtin(t_mini *mini, t_node *node)
{
	char	**aux;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = len_node(mini, node->str);
	aux = malloc(sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i])
	{
		is_in_quote_str(node->str[i], mini, 0);
		if ((!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], ">")
				|| !ft_strcmp(node->str[i], "<<")
				|| !ft_strcmp(node->str[i], ">>"))
			&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]);
	}
	aux[j] = NULL;
	minifree(node->str);
	node->str = aux;
	check_dollar(mini, node);
}
