#include "../include/minishell.h"

void	minicd(t_mini *mini, t_node *node)
{
	t_nodenv	*env; // Ponteiro para variáveis de ambiente
	char		*home; // Ponteiro para variavel HOME

	env = mini->env->begin; // Inicializa env com início da lista
	home = NULL; // Inicializa HOME como nulo
	if (node->str[1]) // Se houver arg. após o "cd"
		g_return = chdir(node->str[1]); // tenta mudar para o diretório especificado
	else 
	{
		while (env != NULL) //Percorre a lista de variavel amabiente 
		{
			if (!ft_strcmp(env->key, "HOME")) //procura por variavel HOME
				home = ft_strdup(env->content); // copia o valor de HOME
			env = env->next; // Avança para o proximo nó
		}
		if (home != NULL) //se HOME for encontrado
		{
			chdir(home); //muda para o diretorio solicitado
			free(home); //libera a memoria
		}
	}
	if (g_return < 0)// se chdir falhar 
		printf("cd: no such file or directory\n"); //mostra o erro
	if (g_return < 0) //se houve o erro
		g_return = 1; //define o codigo de retorno
}