#include "../include/minishell.h"

void	minienv(t_env *env)
{
	print_env(env); //imprime variavel de ambiente
	g_return = 0; //define o retorno com sucesso
}