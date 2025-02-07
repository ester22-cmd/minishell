#include "../include/minishell.h"

void	print(t_mini *mini, t_node *node, int i, int j)
{
	while (node->str[i][j]) // Loop que percorre cada caractere da string atual
	{
		is_in_quote(node->str[i][j], mini); // Verifica se o caractere atual é uma aspas e atualiza o estado
		if (mini->is_open_s == 1 || mini->final_s == 1) // Se estiver dentro de aspas simples ou acabou de fechar
		{
			if (node->str[i][j] != S_QUOTE) // Se não for uma aspas simples
				ft_putchar_fd(node->str[i][j], STDOUT_FILENO); // Imprime o caractere
		}
		if (mini->is_open_d == 1 || mini->final_d == 1) // Se estiver dentro de aspas duplas ou acabou de fechar
		{
			if (node->str[i][j] != D_QUOTE)  // Se não for uma aspas dupla
				ft_putchar_fd(node->str[i][j], STDOUT_FILENO); // Imprime o caractere
		}
		if (mini->is_open_s == 0 && mini->is_open_d == 0 // Se não estiver dentro de nenhuma aspas
			&& mini->final_s == 0 && mini->final_d == 0) // e não acabou de fechar nenhuma aspas
			ft_putchar_fd(node->str[i][j], STDOUT_FILENO); // Imprime o caractere
		else if (mini->final_s == 1 || mini->final_d == 1) // Se acabou de fechar alguma aspas
		{
			mini->final_s = 0; // Reseta flag de aspas simples fechada
			mini->final_d = 0; // Reseta flag de aspas dupla fechada
		}
		j++; // Avança para o próximo caractere
	}
}

void	is_in_quote_str(char *str, t_mini *mini, int i)
{
	while (str[i] != '\0') // Loop que percorre a string
	{
		if (str[i] == S_QUOTE) // Se encontrar aspas simples
		{
			if (mini->is_open_s_str == 0 && mini->is_open_d_str == 0)  // Se não houver aspas abertas
				mini->is_open_s_str = 1; // Marca aspas simples como aberta
			else if (mini->is_open_s_str == 1) // Se aspas simples já estiver aberta
			{
				mini->is_open_s_str = 0; // Fecha as aspas simples
				mini->is_final_s = 1; // Marca que acabou de fechar aspas simples
			}
		}
		if (str[i] == D_QUOTE)
		{
			if (mini->is_open_d_str == 0 && mini->is_open_s_str == 0)  // Se encontrar aspas duplas
				mini->is_open_d_str = 1; // Marca aspas dupla como aberta
			else if (mini->is_open_d_str == 1) // Se aspas dupla já estiver aberta
			{
				mini->is_open_d_str = 0;  // Fecha as aspas dupla
				mini->is_final_d = 1; // Marca que acabou de fechar aspas dupla
			}
		}
		i++;  // Avança para o próximo caractere
	}
}

void	miniecho(t_mini *mini, t_node *node, int i)
{
	mini->final_d = 0;// Inicializa todas as flags relacionadas
	mini->final_s = 0;// a estado de aspas como 0
	mini->is_open_s_str = 0;
	mini->is_open_d_str = 0;
	mini->is_final_s = 0;
	mini->is_final_d = 0;
	while (node->str[i] && !ft_strcmp(node->str[i], "-n")) // Pula todos argumentos -n
		i++;
	if (node->str[i])  // Se ainda houver argumentos para processar
	{
		while (node->str[i]) // Loop que processa cada argumento
		{
			is_in_quote_str(node->str[i], mini, 0);  // Analisa as aspas do argumento atual
			if ((node->str[i][0] == '>' || node->str[i][0] == '<') // Se encontrar redirecionamento
				&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0) // fora de aspas
				break ; // Para de processar
			print(mini, node, i, 0); // Imprime o argumento atual
			if (node->str[i + 1] != NULL) // Se não for o último argumento
				ft_putchar_fd(' ', STDOUT_FILENO); // Imprime um espaço
			i++; // Avança para o próximo argumento
		}
		if (ft_strncmp(node->str[1], "-n\0", 3)) // Se não tiver a opção -n
			ft_putchar_fd('\n', STDOUT_FILENO); // Imprime uma nova linha
	}
	g_return = 0; // Define o código de retorno como sucesso
}