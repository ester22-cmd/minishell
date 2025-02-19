/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:16:45 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 23:16:45 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_env(t_mini *mini, char **environ)
{
	char	**aux;
	int		i;

	mini->env = create_env();
	i = 0;
	while (environ[i])
	{
		aux = ft_split(environ[i], '=');
		push_env(mini->env, aux[0], aux[1]);
		i++;
		minifree(aux);
	}
}

void	get_path(t_mini *mini)
{
	char	*path;
	char	*aux;
	int		i;

	path = getenv("PATH");
	aux = ft_strdup(path);
	if (!aux)
		return ;
	mini->path = ft_split(aux, ':');
	i = 0;
	free(aux);
	while (mini->path[i])
	{
		aux = mini->path[i];
		mini->path[i] = ft_strjoin(aux, "/");
		i++;
		free(aux);
	}
}

void	init(t_mini *mini, char **environ)
{
	get_env(mini, environ);
	get_path(mini);
	mini->home = ft_strdup(getenv("HOME"));
	mini->correct_path = NULL;
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->is_open_d_str = 0;
	mini->is_open_s_str = 0;
	mini->is_final_s = 0;
	mini->is_final_d = 0;
	mini->init_with_arrow = 0;
	mini->pipe = 0;
	mini->redir = 0;
	mini->command_fail = 1;
	mini->input = NULL;
	g_return = 0;
}
