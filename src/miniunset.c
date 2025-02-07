#include "../include/minishell.h"

void	miniunset(t_env *env, t_node *node, t_nodenv *aux, t_nodenv *prev)
{
	while (aux != NULL && node->str[1]) // Enquanto houver nós na lista e um argumento para unset
	{
		if (ft_strcmp(aux->key, node->str[1])) // Se a chave atual for diferente da que queremos remover
		{
			if (aux == env->begin && prev == env->begin) // Se estamos no início da lista
				aux = aux->next; // Apenas avança aux
			else
			{// Se não estamos no início
				aux = aux->next; // Avança aux
				prev = prev->next;   // Avança prev junto
			}
		}
		else // Se encontrou a variável que queremos remover
		{
			prev->next = aux->next; // Ajusta o ponteiro do nó anterior para pular o nó atual
			free(aux->key);                 // Libera a memória da chave
			free(aux->content);             // Libera a memória do conteúdo
			free(aux);                      // Libera a memória do nó
			aux = prev->next;               // Avança para o próximo nó
			break;                          // Sai do loop pois já removeu a variável
		}
	}
	g_return = 0; // Define o código de retorno como sucesso
}
