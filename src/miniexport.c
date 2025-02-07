#include "../include/minishell.h"

void	copy_var(t_env *env, char *str)
{
	t_nodenv	*aux; // Ponteiro auxiliar para percorrer a lista de variáveis
	char		**var; // Array para guardar a chave e valor separados

	var = ft_split(str, '='); // Separa a string em chave e valor usando '=' como delimitador
	aux = env->begin; // Começa do início da lista de variáveis de ambiente
	while (aux != NULL)  // Percorre toda a lista de variáveis
	{
		if (ft_strcmp(aux->key, var[0])) // Se a chave atual for diferente da que procuramos
			aux = aux->next; // Avança para o próximo nó
		else // Se encontrou a chave que procurava
		{
			free(aux->content); // Libera o conteúdo antigo
			if (var[1]) // Se tem um novo valor
				aux->content = ft_strdup(var[1]); // Duplica o novo valor
			else
				aux->content = ft_strdup(""); // Se não tem valor, usa string vazia
			minifree(var); // Libera a memoria do array var
			return ;  //retorna pois já atualizou a variavel
		}
	}
	push_env(env, var[0], var[1]); // Se não encontrou a variável, adiciona uma nova
	minifree(var); // Libera a memoria do array var
}

void	miniexport(t_env *env, t_node *node)
{
	int			j; // Contador para percorrer a string

	j = 0;
	if (node->str[1]) // Se tem argumento para o export
	{
		while (node->str[1][j] != '=' && node->str[1][j]) // Procura o caractere '='
			j++;
		if (node->str[1][j] != '=' || j <= 0// Verifica se é um nome válido:
			|| (!ft_isalpha(node->str[1][0]) && node->str[1][0] != '_')) // deve começar com letra ou _
		{
			g_return = 1; // Se inválido, retorna erro
			return ;
		}
		copy_var(env, node->str[1]); // Se é válido, copia/atualiza a variavel
	}
	else
		print_env(env); // Se não tem argumentos, imprime todas variáveis
	g_return = 0; // Define retorno como sucesso
}