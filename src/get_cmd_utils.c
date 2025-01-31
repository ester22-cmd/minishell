#include "../include/minishell.h"

int	len_node(t_mini *mini, char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		is_in_quote_str(str[i], mini, 0);
		if ((str[i][0] == '<' || str[i][0] == '>')
			&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
			i += 2;
		else
		{
			i++;
			len++;
		}
	}
	return (len + 1);
}

int	is_just_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != D_QUOTE || str[i] != S_QUOTE)
			return (1);
		i++;
	}
	return (0);
}

int	len_quote(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (is_just_quote(str[i]))
			len++;
		i++;
	}
	return (len);
}