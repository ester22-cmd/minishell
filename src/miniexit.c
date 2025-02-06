#include "../include/minishell.h"

void	miniexit(t_mini *mini, t_node *node, t_list *list)
{
	int	code; // Variável para armazenar o código de saída do programa
	int	i; // Variável para contar os caracteres na string do argumento

	code = 0; // Inicializa o código de saída com o valor 0 (sucesso)
	i = 0; // Inicializa o contador de caracteres como 0
	while (node->str[i])  // Laço para contar o número de caracteres do primeiro argumento (node->str[1])
		i++; // Incrementa o contador de caracteres até o final da string
	if (i > 2) // Verifica se o número de caracteres no argumento é maior que 2
		printf("exit: too many arguments\n"); // Se sim, imprime a mensagem de erro
	else // Caso contrário, lida com o código de saída
	{
		if (node->str[1] && ft_strcmp(node->str[1], "exit")) // Verifica se existe um segundo argumento e se ele não é "exit"
			code = ft_atoi(node->str[1]); // Converte o segundo argumento para um inteiro e armazena em 'code'
		free_reset(mini, list); // Função para liberar recursos (não detalhada no código fornecido)
		free_em_all(mini); // Libera todos os recursos associados ao 'mini'
		close(mini->st_out); // Fecha os descritores de arquivo relacionados a saída e entrada padrão
		close(mini->st_in);
		exit(code); //Finaliza o programa com o código de saída especificado
	}
}