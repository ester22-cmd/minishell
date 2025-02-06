#include "../include/minishell.h"

/*
** function that expands variables if it exist
*/
void	check_dollar(t_mini *mini, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->str[i]) // Percorre cada string do array node->str
	{
		j = 0;
		while (node->str[i][j]) // Percorre os caracteres de cada string
		{
			is_in_quote(node->str[i][j], mini); // Verifica se está dentro de aspas
			// Se encontrar um '$' e ele não estiver dentro de aspas simples,
			// além de não ser o último caractere ou um espaço
			if (mini->is_open_s == 0 && node->str[i][j] == '$'
				&& node->str[i][j + 1] != ' ' && node->str[i][j + 1] != '\0')
			{
				expand_var(mini, node, i); // Expande a variável de ambiente
				break ; // Sai do loop interno após expandir
			}
			j++;
		}
		i++;
	}
}

char	*dirty_jobs(char **str, int i)
{
	char	*holder;
	char	*aux;
	int		start;
	int		end;
	int		j;

	j = 0;
	holder = ft_strdup(str[i]); // Duplica a string
	while (holder[j] && holder[j] == ' ') 
		j++;
	while (holder[j] && (holder[j] == D_QUOTE || holder[j] == S_QUOTE))
		j++;
	start = j;  // Define o início da string sem aspas iniciais
	// Avança até encontrar uma aspa ou o final da string
	while (holder[j] && holder[j] != D_QUOTE && holder[j] != S_QUOTE)
		j++;

	end = j - 1;  // Define o final válido da string
	aux = ft_substr(holder, start, end - start + 1);  // Extrai a parte limpa
	free(holder);
	return (aux);
}

char	**remove_quotes(char **str, int len, int i, int k)
{
	char	**aux;

	aux = malloc(sizeof(char *) * len + 1); // Aloca espaço para um novo array de strings
	while (str[i]) // Percorre o array original
	{
		if (is_just_quote(str[i])) // Se a string não for apenas aspas...
		{
			aux[k] = dirty_jobs(str, i); // Remove as aspas
			k++;
		}
		i++;
	}
	aux[k] = NULL; // Finaliza o array com NULL
	return (aux);
}

/*
** function that prepares the right command and cleans it
*/
void	get_cmd(t_mini *mini, t_node *node)
{
	char	**aux;
	char	**holder;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = len_node(mini, node->str); // Conta o número de elementos válidos
	aux = malloc(sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i]) // Percorre a lista de argumentos
	{
		if (node->str[i][0] == '<' || node->str[i][0] == '>') // Ignora operadores de redirecionamento e seus argumentos
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]); // Copia a string
	}
	aux[j] = NULL;
	len = len_node(mini, aux); // Conta novamente os elementos sem redirecionamento
	holder = remove_quotes(aux, len, 0, 0); // Remove aspas desnecessárias
	minifree(node->str); // Libera memória do antigo array
	minifree(aux);
	node->str = holder; // Atualiza o nó com os argumentos tratados
	check_dollar(mini, node); // Expande variáveis de ambiente
}

void	get_cmd_builtin(t_mini *mini, t_node *node)
{
	char	**aux;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = len_node(mini, node->str); // Conta os elementos da lista
	aux = malloc(sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i]) // Percorre os argumentos
	{
		is_in_quote_str(node->str[i], mini, 0); // Verifica aspas
// Se for um operador de redirecionamento E não estiver dentro de aspas, ignora
		if ((!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], ">")
				|| !ft_strcmp(node->str[i], "<<")
				|| !ft_strcmp(node->str[i], ">>"))
			&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]); // Copia argumento válido
	}
	aux[j] = NULL;
	minifree(node->str); // Libera memória do array antigo
	node->str = aux; // Atualiza a estrutura
	check_dollar(mini, node); // Expande variáveis de ambiente
}
