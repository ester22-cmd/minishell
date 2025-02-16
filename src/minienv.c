#include "../include/minishell.h"

void	minienv(t_env *env)
{
	print_env(env);
	g_return = 0;
}