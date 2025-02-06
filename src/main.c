#include "../include/minishell.h"

int	g_return; // Variável global para armazenar o código de retorno do último comando executado

int	main(void)
{// Declaração das estruturas principais
	t_mini	mini; // Estrutura principal do shell, armazena informações do estado
	t_list	*list; // Lista encadeada que armazenará os comandos
	t_sani	sani; // Estrutura usada para sanitizar a entrada do usuário

	init(&mini, __environ); // Inicializa a estrutura mini, passando as variáveis de ambiente do sistema (__environ)
	while (1) // Loop infinito para manter o shell rodando
	{
		signals(1); // Configura os handlers de sinais (provavelmente para Ctrl+C, Ctrl+D, etc.)
	// Define os descritores de entrada e saída como padrão (caso tenham sido alterados por redirecionamentos)
		mini.in = STDIN_FILENO; // Entrada padrão (teclado)
		mini.out = STDOUT_FILENO; // Saída padrão (tela)

		list = create_list(); // Cria uma nova lista encadeada para armazenar os comandos da linha atual
		get_input(&mini, &sani, list); // Obtém a entrada do usuário e armazena na estrutura mini
		if (ft_strlen(mini.input) != 0 && mini.input[0] != '|') // Verifica se o input não está vazio e não começa com '|'
		{
			// Valida a entrada e verifica se todas as aspas foram fechadas corretamente
			if (!input_validate(&mini) || !quotes_closed(&mini))
				printf("error\n"); // Se houver erro, imprime "error"
			else if (split_cmd(&mini, list) && redir_validate(list))
				run(&mini, list, 0); // Se a entrada for válida, divide os comandos e valida redirecionamentos
				// Se tudo estiver correto, executa o comando
		}
		free_reset(&mini, list);// Libera memória e reseta variáveis após cada loop de execução
		mini.pipe = 0; // Reseta o contador de pipes para a próxima execução
	}
	free_em_all(&mini); // Quando o shell é encerrado, libera toda a memória alocada
	return (0); // Retorna 0 indicando que o programa finalizou sem erros
}