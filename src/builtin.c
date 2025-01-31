#include "../include/minishell.h"

int	is_builtin(t_node *node)
{
	if (!node->str[0])
		return (0);
	if (!ft_strncmp(node->str[0], "echo\0", 5))
		return (1);
	if (!ft_strncmp(node->str[0], "cd\0", 3))
		return (2);
	if (!ft_strncmp(node->str[0], "pwd\0", 4))
		return (3);
	if (!ft_strncmp(node->str[0], "export\0", 7))
		return (4);
	if (!ft_strncmp(node->str[0], "unset\0", 6))
		return (5);
	if (!ft_strncmp(node->str[0], "env\0", 4))
		return (6);
	if (!ft_strncmp(node->str[0], "exit\0", 5))
		return (7);
	return (0);
}

void	execute_builtin(int builtin, t_node *node, t_mini *mini, t_list *list)
{
	get_cmd_builtin(mini, node);
	if (builtin == 1)
		miniecho(mini, node, 1);
	if (builtin == 2)
		minicd(mini, node);
	if (builtin == 3)
		minipwd();
	if (builtin == 4)
		miniexport(mini->env, node);
	if (builtin == 5)
		miniunset(mini->env, node, mini->env->begin, mini->env->begin);
	if (builtin == 6)
		minienv(mini->env);
	if (builtin == 7)
		miniexit(mini, node, list);
}