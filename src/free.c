/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:25:33 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 22:25:33 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minifree(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_em_all(t_mini *mini)
{
	t_env	*env;

	env = mini->env;
	free_env(&env);
	minifree(mini->path);
	free(mini->home);
}

void	free_reset(t_mini *mini, t_list *list)
{
	free_list(&list);
	if (mini->input && ft_strlen(mini->input) > 0)
		if (mini->input[0] == '|')
			printf("minihell: syntax error. Unexpected token \'|\'\n");
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->input_sanitized)
	{
		free(mini->input_sanitized);
		mini->input_sanitized = NULL;
	}
	if (mini->correct_path)
	{
		free(mini->correct_path);
		mini->correct_path = NULL;
	}
}
