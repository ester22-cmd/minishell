#include "../include/minishell.h"

int	is_this_quote(char *str) // Função que verifica se a string é uma aspa simples ou dupla, sem outros caracteres
{
	if ((str[0] == D_QUOTE || str[0] == S_QUOTE) && str[1] == '\0') // Verifica se a string tem apenas uma aspa (simples ou dupla)
		return (1); // Retorna 1 se for uma aspa válida
	return (0); // Retorna 0 se não for uma aspa
}

int	get_result(t_mini *mini, t_node *node, int i) // Função que determina o resultado do redirecionamento baseado em tokens
{
	int	result; // Variável para armazenar o resultado (1 por padrão)

	result = 1; // Inicializa o resultado com 1 (sucesso)
	if (mini->open_s_str == 0 && mini->open_d_str == 0 // Verifica se não está dentro de aspas e se o token é um redirecionamento de saída ("<" ou "<<")
		&& (!ft_strcmp(node->str[i], ">") || !ft_strcmp(node->str[i], ">>")))
		result = redirect_out(mini, node, i); // Chama a função de redirecionamento de saída
	if (mini->open_s_str == 0 && mini->open_d_str == 0 // Verifica se não está dentro de aspas e se o token é um redirecionamento de entrada ("<" ou "<<")
		&& (!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], "<<")))
		result = redirect_in(mini, node, i); // Chama a função de redirecionamento de entrada
	return (result); // Retorna o resultado do redirecionamento (1 para sucesso, 0 para falha)
}

void	fd_handler(t_mini *mini) // Função que manipula os descritores de arquivos para redirecionamento
{
	(void)mini; // Ignora o ponteiro "mini" para evitar warnings (não está sendo usado aqui)
	if (mini->in != 0) // Verifica se existe um descritor de entrada válido
	{
		dup2(mini->in, STDIN_FILENO); // Redireciona o descritor de entrada para a entrada padrão (STDIN)
		close(mini->in); // Fecha o descritor de entrada após a duplicação
	}
	if (mini->out != 1) // Verifica se existe um descritor de saída válido (1 é a saída padrão)
	{
		dup2(mini->out, STDOUT_FILENO); // Redireciona o descritor de saída para a saída padrão (STDOUT)
		close(mini->out); // Fecha o descritor de saída após a duplicação
	}
}

int	is_str_quote(char *str, int open) // Função que verifica se a string contém uma aspa simples ou dupla
{
	if (open == 0 && str[0] == D_QUOTE && str[1] == '\0') // Se não estiver dentro de aspas e for uma aspa dupla
		return (1);// Retorna 1 (abertura da aspa dupla)
	else if (open == 1 && str[0] == D_QUOTE && str[1] == '\0') // Se estiver dentro de aspas e for uma aspa dupla
		return (0); // Retorna 0 (fechamento da aspa dupla)
	else if (open == 0 && str[0] == S_QUOTE && str[1] == '\0') // Se não estiver dentro de aspas e for uma aspa simples
		return (1); // Retorna 1 (abertura da aspa simples)
	else if (open == 1 && str[0] == S_QUOTE && str[1] == '\0') // Se estiver dentro de aspas e for uma aspa simples
		return (0); // Retorna 0 (fechamento da aspa simples)
	return (0); // Retorna 0 se não for nenhuma das opções acima
}