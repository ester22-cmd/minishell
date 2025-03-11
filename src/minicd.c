/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:17:13 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 23:17:13 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void change_directory(char *path)
{
	if (chdir(path) < 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		g_return = 1;
	}
	else
	{
		g_return = 0;
	}
}

void minicd(t_mini *mini, t_node *node)
{
	t_nodenv *env = mini->env->begin;

	if (node->str[1] && node->str[2])
	{
		printf("cd: too many arguments\n");
		g_return = 1;
		return;
	}

	if (node->str[1])
	{
		change_directory(node->str[1]);
		return;
	}

	while (env && ft_strcmp(env->key, "HOME"))
		env = env->next;

	if (!env)
	{
		printf("cd: HOME not set\n");
		g_return = 1;
		return;
	}

	change_directory(env->content);
}
