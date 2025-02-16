/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:05:51 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 21:05:51 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_home(t_mini *mini)
{
	t_nodenv	*env;

	env = mini->env->begin;
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, "HOME"))
			break ;
		env = env->next;
	}
	if (env->content)
	{
		free(mini->home);
		mini->home = ft_strdup(env->content);
	}
}

char	*copy_string(t_mini *mini, char *cmd, int len_home, int tilda)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = malloc (sizeof(char) * len_home + ft_strlen(cmd) + 1 - tilda);
	while (cmd[i])
	{
		if (cmd[i] != '~')
			str[j++] = cmd[i++];
		else
		{
			if (i != 0)
				k++;
			while (mini->home[k])
				str[j++] = mini->home[k++];
			k = 0;
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	*copy_path(t_mini *mini, char *cmd, int tilda)
{
	char	*aux;
	int		len_home;
	int		i;

	len_home = ft_strlen(mini->home);
	i = 0;
	if (cmd[i] == '~')
		len_home++;
	aux = copy_string(mini, cmd, len_home, tilda);
	return (aux);
}
