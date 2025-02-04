#include "../include/minishell.h"

t_env	*create_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env)); // Aloca memória para uma nova estrutura de ambiente
	env->begin = NULL; // Inicializa os ponteiros de início e fim como NULL
	env->end = NULL;
	env->size = 0; // Inicializa o tamanho como 0
	return (env);  // Retorna a estrutura de ambiente criada
}

t_nodenv	*create_nodenv(char *key, char *content)
{
	t_nodenv	*node;
 // Aloca memória para um novo nó de ambiente
	node = malloc(sizeof(t_nodenv));
	node->key = ft_strdup(key); // Copia a chave (nome da variável de ambiente)
// Se o conteúdo for fornecido, copia-o
	if (content)
		node->content = ft_strdup(content);
	else
// Se não houver conteúdo, usa uma string vazia
		node->content = ft_strdup("");
// Inicializa o ponteiro para o próximo nó como NULL
	node->next = NULL;
	return (node); // Retorna o nó criado
}

void	push_env(t_env *env, char *key, char *content)
{
	t_nodenv	*node;
// Cria um novo nó de ambiente
	node = create_nodenv(key, content);
// Se a lista estiver vazia
	if (env->begin == NULL)
	{
// Define o novo nó como início e fim da lista
		env->begin = node;
		env->end = node;
	}
	else
	{
// Adiciona o novo nó ao final da lista
		env->end->next = node;
		env->end = env->end->next;
	}
// Incrementa o tamanho da lista
	env->size++;
}

void	free_env(t_env **env_ref)
{
	t_env		*env;
	t_nodenv	*node;
	t_nodenv	*aux;
// Obtém o ponteiro para a estrutura de ambiente
	env = *env_ref;
	node = env->begin; // Ponteiro para percorrer a lista
	aux = NULL;
// Percorre toda a lista
	while (node != NULL)
	{
		aux = node; // Guarda o nó atual
		node = node->next; // Move para o próximo nó
// Libera a memória do nó atual
		free(aux->key);
		free(aux->content);
		free(aux);
	}
// Libera a estrutura de ambiente
	free(env);
// Define o ponteiro original como NULL
	*env_ref = NULL;
}

void	print_env(t_env *env)
{
	t_nodenv	*node;
// Ponteiro para percorrer a lista
	node = env->begin;
// Percorre todos os nós, exceto o último
	while (node->next != NULL)
	{
// Imprime cada variável de ambiente no formato chave=valor
		printf("%s=%s\n", node->key, node->content);
		node = node->next;
	}
// Imprime o último nó
	printf("%s=%s\n", node->key, node->content);
}