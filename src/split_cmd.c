/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:20:25 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 23:20:25 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	dirty_job_handler(t_mini *mini, t_list *list, char *str, int start)
{
	if (mini->input_sanitized[mini->i + 1] == '\0' && mini->is_open_s == 0
		&& mini->is_open_d == 0)
	{
		str = ft_substr(mini->input_sanitized, start, mini->i - start + 1);

		if (!is_space(str))
		{
			free(str);
			return (0);
		}
		push_node(list, str);
		free(str);
	}
	return (1);
}

void	dirty_job(t_mini *m, t_list *list, int start)
{
	char	*str;

	while (m->input_sanitized[m->i])
	{
		is_in_quote(m->input_sanitized[m->i], m);
		if (m->input_sanitized[m->i] == '|' && m->is_open_s == 0
			&& m->is_open_d == 0)
		{
			str = ft_substr(m->input_sanitized, start, (m->i - 1) - start);
			m->i++;
			start = m->i;

			if (!is_space(str))
			{
				m->pipe--;
				free(str);
				return ;
			}
			push_node(list, str);
			free(str);
			m->pipe++;
		}
		if (dirty_job_handler(m, list, str, start) == 0)
			return ;
		m->i++;
	}
}

int	split_cmd(t_mini *mini, t_list *list)
{
	int		start;

	mini->i = 0;
	start = mini->i;
	dirty_job(mini, list, start);
	if (mini->is_open_s == 1 || mini->is_open_d == 1)
		return (0);
	return (1);
}