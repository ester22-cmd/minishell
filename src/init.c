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
	#include "../include/minishell.h"

void	miniexit(t_mini *mini, t_node *node, t_list *list)
{
	int	code;
	int	i;

	code = 0;
	i = 0;
	while (node->str[i]) 
		i++;
	if (i > 2)
		printf("exit: too many arguments\n");
	else
	{
		if (node->str[1] && ft_strcmp(node->str[1], "exit"))
			code = ft_atoi(node->str[1]);
		free_reset(mini, list);
		free_em_all(mini);
		close(mini->st_out);
		close(mini->st_in);
		exit(code);
	}
}while (environ[i])
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
	g_return = 0;
}
