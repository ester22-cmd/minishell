/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:16:57 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 23:16:57 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quotes_closed(t_mini *mini)
{
	int	i;

	i = 0;
	mini->is_open_d = 0;
	mini->is_open_s = 0;
	while (mini->input[i])
	{
		is_in_quote(mini->input[i], mini);
		i++;
	}
	if (mini->is_open_d == 1 || mini->is_open_s == 1)
		return (0);
	return (1);
}

int	input_validate(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->input[i])
	{
		is_in_quote(mini->input[i], mini);
		if (mini->input[i] == '<' && mini->input[i + 1] == '|'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		else if (mini->input[i] == '>' && mini->input[i + 1] == '|'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		else if (mini->input[i] == '>' && mini->input[i + 1] == '<'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		else if (mini->input[i] == '<' && mini->input[i + 1] == '>'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_validate(t_hand *hand, char	*str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		count = 0;
		if (hand->open == 0 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
			hand->open = 1;
		else if (hand->open == 1 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
			hand->open = 0;
		while (hand->open == 0 && (str[i] == '<' || str[i] == '>'))
		{
			i++;
			count++;
		}
		if (count >= 3)
			return (0);
		i++;
	}
	return (1);
}

int	redir_validate(t_list *list)
{
	t_node	*node;
	t_hand	hand;
	int		i;

	node = list->begin;
	hand.open = 0;
	while (node != NULL)
	{
		i = 0;
		while (node->str[i])
		{
			if (!check_validate(&hand, node->str[i]))
			{
				printf("redir error\n");
				return (0);
			}
			i++;
		}
		node = node->next;
	}
	return (1);
}

void	get_input(t_mini *mini, t_sani *sani, t_list *list)
{
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->input = readline("minihell's>>");
	if (mini->input)
	{
		if (ft_strlen(mini->input) != 0)
			add_history(mini->input);
		input_sanitizer(mini, sani);
	}
	else
	{
		free_list(&list);
		free(mini->input_sanitized);
		if (mini->correct_path != NULL)
			free(mini->correct_path);
		free_em_all(mini);
		printf("exit\n");
		exit(130);
	}
}
