#include "../include/minishell.h"

int	quotes_closed(t_mini *mini)
{
	int	i;
// Inicializa um contador
	i = 0;
// Reseta os flags de aspas
	mini->is_open_d = 0;
	mini->is_open_s = 0;
// Percorre toda a entrada do usuário
	while (mini->input[i])
	{
	// Verifica o estado das aspas para cada caractere
		is_in_quote(mini->input[i], mini);
		i++;
	}
	// Se alguma aspas (simples ou dupla) permanecer aberta,
	// retorna 0 (inválido)
	if (mini->is_open_d == 1 || mini->is_open_s == 1)
		return (0);
	return (1); // Caso contrário, retorna 1 (válido)
}

int	input_validate(t_mini *mini)
{
	int	i;

	i = 0;
	// Percorre toda a entrada do usuário
	while (mini->input[i])
	{
		is_in_quote(mini->input[i], mini); // Verifica o estado das aspas para cada caractere
	// Verifica sequências inválidas de redirecionadores e pipes
	// Fora de contexto de aspas
		if (mini->input[i] == '<' && mini->input[i + 1] == '|'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		else if (mini->input[i] == '>' && mini->input[i + 1] == '|'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		else if (mini->input[i] == '>' && mini->input[i + 1] == '<'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		else if (mini->input[i] == '<' && mini->input[i + 1] == '>'
			&& mini->is_open_s == 0 && mini->is_open_d == 0)
			return (0);
		i++;
	}
	return (1); // Se passar por todas as verificações, retorna 1 (válido)
}

/*
** function that check sequences of '<' and '>'
*/
int	check_validate(t_hand *hand, char	*str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		count = 0; // Reseta o contador de redirecionadores
		// Controle de estado de aspas
		if (hand->open == 0 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
			hand->open = 1;
		else if (hand->open == 1 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
			hand->open = 0;
		// Conta sequências de redirecionadores fora de aspas
		while (hand->open == 0 && (str[i] == '<' || str[i] == '>'))
		{
			i++;
			count++;
		}
		if (count >= 3) // Se mais de 2 redirecionadores seguidos, retorna inválido
			return (0);
		i++;
	}
	return (1); // Se passou por todas as verificações, retorna válido
}

int	redir_validate(t_list *list)
{
	t_node	*node;
	t_hand	hand;
	int		i;

	node = list->begin; // Ponteiro para o primeiro nó da lista
	hand.open = 0; // Estrutura para controle de aspas
	while (node != NULL) // Estrutura para controle de aspas
	{
		i = 0;
		while (node->str[i]) // Valida cada string do nó
		{// Se encontrar sequência inválida de redirecionadores
			if (!check_validate(&hand, node->str[i]))
			{
				printf("redir error\n");
				return (0);
			}
			i++;
		}
		node = node->next; // Passa para o próximo nó
	}
	return (1); // Se passou por todos os nós sem erro, retorna válido
}

/*
** function that takes input from user and add to the history
*/
void	get_input(t_mini *mini, t_sani *sani, t_list *list)
{// Reseta flags de aspas
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->input = readline(">> "); // Lê input do usuário com prompt
	// Se input não for vazio, adiciona ao histórico
	if (mini->input)
	{
		if (ft_strlen(mini->input) != 0)
			add_history(mini->input);
		input_sanitizer(mini, sani); // Sanitiza o input
	}
	else
	{
		free_list(&list); // Se input for NULL (Ctrl+D), limpa memória e sai
		free(mini->input_sanitized);
		if (mini->correct_path != NULL)
			free(mini->correct_path);
		free_em_all(mini);
		printf("exit\n");
		exit(130);
	}
}
