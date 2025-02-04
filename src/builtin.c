#include "../include/minishell.h"

int	is_builtin(t_node *node)
{// Verifica se o primeiro elemento do array de strings está vazio
	// Retorna 0 se não houver comando
	if (!node->str[0])
		return (0);
// Verifica se o comando é "echo"
	// Compara os primeiros 5 caracteres (incluindo o terminador nulo)
	// Retorna 1 se for um comando "echo"

	if (!ft_strncmp(node->str[0], "echo\0", 5))
		return (1);

	// Verifica se o comando é "cd"
	// Compara os primeiros 3 caracteres (incluindo o terminador nulo)
	// Retorna 2 se for um comando "cd"
	if (!ft_strncmp(node->str[0], "cd\0", 3))
		return (2);

// Verifica se o comando é "pwd"
	// Compara os primeiros 4 caracteres (incluindo o terminador nulo)
	// Retorna 3 se for um comando "pwd"

	if (!ft_strncmp(node->str[0], "pwd\0", 4))
		return (3);

// Verifica se o comando é "export"
	// Compara os primeiros 7 caracteres (incluindo o terminador nulo)
	// Retorna 4 se for um comando "export"

	if (!ft_strncmp(node->str[0], "export\0", 7))
		return (4);
// Verifica se o comando é "unset"
	// Compara os primeiros 6 caracteres (incluindo o terminador nulo)
	// Retorna 5 se for um comando "unset"

	if (!ft_strncmp(node->str[0], "unset\0", 6))
		return (5);
// Verifica se o comando é "env"
	// Compara os primeiros 4 caracteres (incluindo o terminador nulo)
	// Retorna 6 se for um comando "env"

	if (!ft_strncmp(node->str[0], "env\0", 4))
		return (6);

	// Verifica se o comando é "exit"
	// Compara os primeiros 5 caracteres (incluindo o terminador nulo)
	// Retorna 7 se for um comando "exit"

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