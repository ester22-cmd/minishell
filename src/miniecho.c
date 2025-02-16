#include "../include/minishell.h"

void	print(t_mini *mini, t_node *node, int i, int j)
{
	while (node->str[i][j])
	while (node->str[i][j])
	{
		is_in_quote(node->str[i][j], mini);
		if (mini->is_open_s == 1 || mini->final_s == 1)
		{
			if (node->str[i][j] != S_QUOTE)
				ft_putchar_fd(node->str[i][j], STDOUT_FILENO);
		}
		if (mini->is_open_d == 1 || mini->final_d == 1)
		if (mini->is_open_d == 1 || mini->final_d == 1)
		{
			if (node->str[i][j] != D_QUOTE)
				ft_putchar_fd(node->str[i][j], STDOUT_FILENO);
			if (node->str[i][j] != D_QUOTE)
				ft_putchar_fd(node->str[i][j], STDOUT_FILENO);
		}
		if (mini->is_open_s == 0 && mini->is_open_d == 0
			&& mini->final_s == 0 && mini->final_d == 0)
			ft_putchar_fd(node->str[i][j], STDOUT_FILENO);
		else if (mini->final_s == 1 || mini->final_d == 1)
		if (mini->is_open_s == 0 && mini->is_open_d == 0
			&& mini->final_s == 0 && mini->final_d == 0)
			ft_putchar_fd(node->str[i][j], STDOUT_FILENO);
		else if (mini->final_s == 1 || mini->final_d == 1)
		{
			mini->final_s = 0;
			mini->final_d = 0;
			mini->final_s = 0;
			mini->final_d = 0;
		}
		j++;
		j++;
	}
}

void	is_in_quote_str(char *str, t_mini *mini, int i)
{
	while (str[i] != '\0')
	while (str[i] != '\0')
	{
		if (str[i] == S_QUOTE)
		{
			if (mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
				mini->is_open_s_str = 1;
			else if (mini->is_open_s_str == 1)
			if (mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
				mini->is_open_s_str = 1;
			else if (mini->is_open_s_str == 1)
			{
				mini->is_open_s_str = 0;
				mini->is_final_s = 1;
				mini->is_open_s_str = 0;
				mini->is_final_s = 1;
			}
		}
		if (str[i] == D_QUOTE)
		{
			if (mini->is_open_d_str == 0 && mini->is_open_s_str == 0)
				mini->is_open_d_str = 1;
			else if (mini->is_open_d_str == 1)
			if (mini->is_open_d_str == 0 && mini->is_open_s_str == 0)
				mini->is_open_d_str = 1;
			else if (mini->is_open_d_str == 1)
			{
				mini->is_open_d_str = 0;
				mini->is_final_d = 1;
				mini->is_open_d_str = 0;
				mini->is_final_d = 1;
			}
		}
		i++;
		i++;
	}
}

void	miniecho(t_mini *mini, t_node *node, int i)
{
	mini->final_d = 0;
	mini->final_s = 0;
	mini->final_d = 0;
	mini->final_s = 0;
	mini->is_open_s_str = 0;
	mini->is_open_d_str = 0;
	mini->is_final_s = 0;
	mini->is_final_d = 0;
	while (node->str[i] && !ft_strcmp(node->str[i], "-n"))
	while (node->str[i] && !ft_strcmp(node->str[i], "-n"))
		i++;
	if (node->str[i])
	if (node->str[i])
	{
		while (node->str[i])
		while (node->str[i])
		{
			is_in_quote_str(node->str[i], mini, 0);
			if ((node->str[i][0] == '>' || node->str[i][0] == '<')
				&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
				break ;
			print(mini, node, i, 0);
			if (node->str[i + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
			is_in_quote_str(node->str[i], mini, 0);
			if ((node->str[i][0] == '>' || node->str[i][0] == '<')
				&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
				break ;
			print(mini, node, i, 0);
			if (node->str[i + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
		if (ft_strncmp(node->str[1], "-n\0", 3))
			ft_putchar_fd('\n', STDOUT_FILENO);
		if (ft_strncmp(node->str[1], "-n\0", 3))
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_return = 0;
	g_return = 0;
}