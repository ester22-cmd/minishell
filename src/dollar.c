#include "../include/minishell.h"

char	*get_var_content(t_mini *mini, char *key) //Busca o conteúdo de uma variável de ambiente na lista encadeada de variáveis
{
	t_nodenv	*node_env; // Ponteiro para percorrer a lista de variáveis de ambiente

	node_env = mini->env->begin; // Começa do início da lista de ambiente
	while (node_env != NULL) // Percorre toda a lista
	{
		if (!ft_strcmp(node_env->key, key))   // Se encontrar a chave procurada
			return (ft_strdup(node_env->content)); // Retorna uma cópia do conteúdo
		node_env = node_env->next; 
	}
	return (NULL); // Se não encontrou, retorna NULL
}

char	*get_var(t_mini *mini, char *str, int i) //Extrai uma variável de uma string e busca seu conteúdo
{
	char	*var; // Armazenará o nome da variável
	char	*content; // Armazenará o conteúdo da variável
	int		len; // Armazenará o conteúdo da variável
	int		j; // Índice auxiliar

	len = 0;
	j = i;
	while (str[i] && str[i] != '$') // Conta o comprimento até encontrar $ ou fim da string
	{
		len++;
		i++;
	}
	if (len > 0) // Aloca espaço para o nome da variável
	{
		var = malloc (sizeof(char) * len + 1);
		i = 0;
		while (str[j] && str[j] != '$' && str[j] != D_QUOTE) // Copia o nome da variável
			var[i++] = str[j++];
		var[i] = '\0';
		content = get_var_content(mini, var); // Busca o conteúdo da variável
		free(var);
		return (content);
	}
	return (NULL);
}

char	*get_join(char *str) // Extrai a parte inicial de uma string até encontrar um $
{
	int		i;
	char	*aux;

	i = 0;
	if (str[i] == '$') // Se começar com $, retorna NULL
		return (NULL);
	while (str[i] && str[i] != '$') // Avança até encontrar $ ou fim da string
		i++;
	aux = ft_substr(str, 0, i - 1); // Extrai a substring até o caractere anterior ao $
	return (aux);
}

char	*get_content(t_mini *mini, t_node *node, int i, int j) //Obtém o conteúdo de uma variável especial ou de ambiente
{
	char	*content;

	content = NULL;
	if (node->str[i][j + 1] == '?') // Se for $?, retorna o código de retorno global
		content = ft_itoa(g_return);
	else // Senão, busca o conteúdo da variável
		content = get_var(mini, node->str[i], j + 1);
	return (content);
}

char	*transform(t_mini *mini, t_node *node, int i, int j) //Transforma uma string expandindo suas variáveis
{
	char	*content; // Conteúdo da variável atual
	char	*holder; // String resultante
	char	*aux;  // String auxiliar para concatenação

	content = NULL;
	// Obtém a parte inicial até o primeiro $
	holder = get_join(node->str[i]);
	while (node->str[i][j]) // Percorre a string
	{
		if (node->str[i][j] == '$') // Quando encontra uma variável
		{
			content = get_content(mini, node, i, j); // Obtém o conteúdo da variável
			if (content != NULL)
			{
				aux = holder;
				if (holder == NULL) // Se holder for NULL, começa com string vazia
					aux = ft_strdup("");
			// Concatena o conteúdo atual
				holder = ft_strjoin(aux, content);
				free(aux);
				free(content);
			}
		}
		j++;
	}
	return (holder);
}