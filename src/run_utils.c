#include "../include/minishell.h"

int	is_this_quote(char *str)// Define a função que verifica se a string é uma citação
{
	if ((str[0] == D_QUOTE || str[0] == S_QUOTE) && str[1] == '\0')
		return (1);// Verifica se o primeiro caractere é uma aspa e se é a única na string
	return (0);
}

int	get_result(t_mini *mini, t_node *node, int i)
{
	int	result;

	result = 1;
	if (mini->open_s_str == 0 && mini->open_d_str == 0
		&& (!ft_strcmp(node->str[i], ">") || !ft_strcmp(node->str[i], ">>")))// Chama a função de redirecionamento de saída e armazena o resultado
		result = redirect_out(mini, node, i);
	if (mini->open_s_str == 0 && mini->open_d_str == 0
		&& (!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], "<<")))// Verifica novamente se não há strings abertas e se o elemento atual é um redirecionamento de entrada
		result = redirect_in(mini, node, i);
	return (result);
}

void	fd_handler(t_mini *mini)// Define a função fd_handler que manipula os descritores de arquivo
{
{
	(void)mini;// Evita um aviso de compilação sobre a variável 'mini' não utilizada (se não for utilizada)
	if (mini->in != 0)// Verifica se o descritor de entrada não é o padrão (0)
	{
	{
		dup2(mini->in, STDIN_FILENO);// Duplica o descritor de entrada para o padrão de entrada (STDIN)
		close(mini->in);
	}
	if (mini->out != 1) // Verifica se o descritor de saída não é o padrão (1)
	{
		dup2(mini->out, STDOUT_FILENO);// Duplica o descritor de saída para o padrão de saída (STDOUT)
		close(mini->out);// Fecha o descritor de saída original, pois não é mais necessário
	}
}

int	is_str_quote(char *str, int open)// Define a função que verifica se a string é uma citação com base no estado 'open'
{
	if (open == 0 && str[0] == D_QUOTE && str[1] == '\0')
		return (1);// Verifica se 'open' é 0 e se a string é uma aspa dupla vazia
	else if (open == 1 && str[0] == D_QUOTE && str[1] == '\0')
		return (0);// Verifica se 'open' é 1 e se a string é uma aspa dupla vazia
	else if (open == 0 && str[0] == S_QUOTE && str[1] == '\0')
		return (1);// Verifica se 'open' é 0 e se a string é uma aspa simples vazia
	else if (open == 1 && str[0] == S_QUOTE && str[1] == '\0')
		return (0);
	return (0);
}