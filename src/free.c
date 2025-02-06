#include "../include/minishell.h"

void	minifree(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i]) //Percorre o array de strings (char **ptr)
	{
		free(ptr[i]); // Libera cada string individualmente
		i++;
	}
	free(ptr);// Libera o array principal
	ptr = NULL; // Define o ponteiro como NULL para evitar *dangling pointers*
}

void	free_reset(t_mini *mini, t_list *list)
{
	free_list(&list); // Libera a lista encadeada de comandos

	if (ft_strlen(mini->input) > 0) // Se houver uma entrada do usuário...
	{
		if (mini->input[0] == '|') // Verifica erro de sintaxe no início
			printf("minihell: syntax error. Unexpected token \'|\'\n");
		free(mini->input); // Libera a entrada do usuário
	}
	free(mini->input_sanitized); // Libera a entrada sanitizada
	if (mini->correct_path != NULL)
		free(mini->correct_path); // Libera o caminho correto, se existir
}

void	free_em_all(t_mini *mini)
{
	t_env	*env;

	env = mini->env;
	free_env(&env); // Libera as variáveis de ambiente
	minifree(mini->path); // Libera o array de caminhos do PATH
	free(mini->home); // Libera a string do diretório home
}
