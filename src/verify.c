#include "../include/minishell.h"

void	is_in_quote(char c, t_mini *mini)
{// Se encontrar uma aspa simples (')
	if (c == S_QUOTE)
	{
		// Se não houver nenhuma aspa aberta (simples ou dupla), marca aspa simples
		if (mini->is_open_s == 0 && mini->is_open_d == 0)
			mini->is_open_s = 1;
		 // Se já havia uma aspa simples aberta, fecha ela e marca como finalizada
		else if (mini->is_open_s == 1)
		{
			mini->is_open_s = 0;
			mini->final_s = 1;
		}
	}
	// Se encontrar uma aspa dupla (")
	if (c == D_QUOTE)
	{
		// Se não houver nenhuma aspa aberta (simples ou dupla), marca aspa dupla como aberta
		if (mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->is_open_d = 1;
	// Se já havia uma aspa dupla aberta, fecha ela e marca como finalizada
		else if (mini->is_open_d == 1)
		{
			mini->is_open_d = 0;
			mini->final_d = 1;
		}
	}
}
// Função que verifica se o caractere é um operador de redirecionamento
int	is_redirect(char c)
{ // Retorna 1 se o caractere for pipe (|) ou redirecionamento (< ou >)
	if (c == '|' || c == '<' || c == '>')
		return (1);

	return (0);
}