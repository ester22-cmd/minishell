#include "../include/minishell.h"

int	is_this_quote(char *str)
{
	if ((str[0] == D_QUOTE || str[0] == S_QUOTE) && str[1] == '\0')
		return (1);
	return (0);

int	get_result(t_mini *mini, t_node *node, int i)
{
	int	result;
	result = 1; 
	if (mini->open_s_str == 0 && mini->open_d_str == 0
		&& (!ft_strcmp(node->str[i], ">") || !ft_strcmp(node->str[i], ">>")))
		result = redirect_out(mini, node, i);
	if (mini->open_s_str == 0 && mini->open_d_str == 0
		&& (!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], "<<")))
		result = redirect_in(mini, node, i);
	return (result); 
void	fd_handler(t_mini *mini)
	(void)mini;
	if (mini->in != 0)
	{
		dup2(mini->in, STDIN_FILENO);
		close(mini->in);
	}
	if (mini->out != 1)
	{
		dup2(mini->out, STDOUT_FILENO);
		close(mini->out);
}

int	is_str_quote(char *str, int open)
{
	if (open == 0 && str[0] == D_QUOTE && str[1] == '\0')
		return (1);
	else if (open == 1 && str[0] == D_QUOTE && str[1] == '\0')
		return (0);
	else if (open == 0 && str[0] == S_QUOTE && str[1] == '\0')
		return (1);
	else if (open == 1 && str[0] == S_QUOTE && str[1] == '\0')
		return (0);
	return (0);
}