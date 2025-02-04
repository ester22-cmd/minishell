#include "../include/minishell.h"

void	expand_var(t_mini *mini, t_node *node, int i) //Função responsável por expandir variáveis de ambiente em um nó do minishell
{
	char		*holder;

	holder = transform(mini, node, i, 0); //Chama a função transform que faz a expansão real da variável O último parâmetro 0 pode ser uma flag de comportamento
	if (holder != NULL) // Verifica se a transformação foi bem sucedida
	{
		free(node->str[i]); //Libera a memória do string original no nó
		node->str[i] = ft_strdup(holder); //Duplica o string transformado para o nó usando ft_strdup (versão própria de strdup)
		free(holder); // Libera a memória temporária alocada para holder
	}
	else
	{
		free(node->str[i]); //Se a transformação falhou (holder é NULL) Libera a memória do string original
		node->str[i] = ft_strdup(" "); //Substitui por um espaço em branco Isto evita strings vazios que poderiam causar problemas
	}
}