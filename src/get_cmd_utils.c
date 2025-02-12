#include "../include/minishell.h"

int	len_node(t_mini *mini, char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i]) // Percorre o array de strings
	{
		is_in_quote_str(str[i], mini, 0); // Verifica se há aspas abertas na string atual
	// Se o primeiro caractere for '<' ou '>' e não estivermos dentro de aspas	
		if ((str[i][0] == '<' || str[i][0] == '>')
			&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
			i += 2;// Pula dois elementos (provavelmente um operador de redirecionamento e seu argumento)
		else
		{
			i++; // Avança para a próxima string
			len++; // Incrementa o comprimento da contagem
		}
	}
	return (len + 1); // Retorna o tamanho total do "nó" (+1 possivelmente para acomodar `NULL`)
}

int	is_just_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i]) // Percorre a string
	{ // Se encontrar qualquer caractere diferente de aspas simples ou duplas, retorna 1
		if (str[i] != D_QUOTE || str[i] != S_QUOTE) //chat diz que tem que colocar && e não ||
			return (1);
		i++;
	}
	return (0); // Se só houver aspas na string, retorna 0
}

int	len_quote(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i]) // Percorre o array de strings
	{
		if (is_just_quote(str[i])) // Se a string não for só aspas, incrementa o contador
			len++;
		i++;
	}
	return (len); // Retorna o número de strings válidas (não apenas aspas)
}