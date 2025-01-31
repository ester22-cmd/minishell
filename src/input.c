#include "../include/minishell.h"

int	quotes_closed(t_mini *mini)
{
	int	i;

	i = 0;
	// Inicializa flags de aspas como fechadas (0)
	mini->is_open_d = 0;
	mini->is_open_s = 0;
	// Percorre cada caractere do input
	while (mini->input[i])
	{
		// Verifica se o caractere atual abre/fecha aspas
		is_in_quote(mini->input[i], mini);
		i++;
	}
	// Se alguma aspas ficou aberta, retorna erro
	if (mini->is_open_d == 1 || mini->is_open_s == 1)
	{
		print_error(ERR_QUOTE_UNBALANCED, NULL);
		return (0);
	}
	return (1);
}

int	input_validate(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->input[i])
	{
		// Verifica estado das aspas para cada caractere
		is_in_quote(mini->input[i], mini);
		// Se não estiver dentro de aspas, verifica combinações inválidas:
		if (mini->is_open_s == 0 && mini->is_open_d == 0)
		{
			// Verifica sequências inválidas de redirecionamentos:
            // <| - redirecionamento seguido de pipe
            // >| - redirecionamento seguido de pipe
            // >< - redirecionamentos opostos seguidos
            // <> - redirecionamentos opostos seguidos
			if ((mini->input[i] == '<' && mini->input[i + 1] == '|') ||
                (mini->input[i] == '>' && mini->input[i + 1] == '|') ||
                (mini->input[i] == '>' && mini->input[i + 1] == '<') ||
                (mini->input[i] == '<' && mini->input[i + 1] == '>'))
                return (0);
		}
		i++;
	return (1);
}

int	check_validate(t_hand *hand, char	*str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		count = 0;
		// Controla se está dentro ou fora de aspas
		if (hand->open == 0 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
			hand->open = 1;
		else if (hand->open == 1 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
			hand->open = 0;
		// Se não estiver em aspas, conta redirecionamentos consecutivos
		while (hand->open == 0 && (str[i] == '<' || str[i] == '>'))
		{
			i++;
			count++;
		}
		 // Não permite mais de 2 redirecionamentos consecutivos
		if (count >= 3)
			return (0);
		i++;
	}
	return (1);
}

int	redir_validate(t_list *list)
{
	t_node	*node;
	t_hand	hand;
	int		i;

	node = list->begin;
	hand.open = 0;
	// Percorre a lista de tokens
	while (node != NULL)
	{
		i = 0;
		while (node->str[i])
		{
			// Verifica redirecionamentos em cada token
			if (!check_validate(&hand, node->str[i]))
		{
				write(1, "redir error\n", 14);
				return (0);
			}
			i++;
		}
		node = node->next;
	}
	return (1);
}
void	get_input(t_mini *mini, t_sani *sani, t_list *list)
{// Inicializa flags de aspas
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	// Lê uma linha do terminal
	mini->input = readline(">> ");
	// Se Ctrl+D foi pressionado (EOF)
	if (!mini->input)
	{
		cleanup_input(mini, list);
		write(1, "exit\n", 6);
		exit(130);
	}
	// Valida o input
	if(!validate_input(mini))
	{
		safe_free((void **)&mini->input);
		return;
	}
	 // Adiciona ao histórico se não for vazio
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	// Sanitiza o input (remove espaços extras, etc)
	input_sanitizer(mini, sani);
}
void	cleanup_input(t_mini *mini, t_list *list)
{// Libera todas as memórias alocadas
	safe_free((void **)&mini->input);
	safe_free((void **)&mini->input_sanitized);
	if (mini->correct_path)
		safe_free((void **)&mini->correct_path);
	free_list(&list);
	free_em_all(mini);
}
