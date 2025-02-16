#include "../include/minishell.h"

int	g_return; // Variável global para armazenar o código de retorno do último comando executado

int	main(void)
{// Declaração das estruturas principais
	t_mini	mini; // Estrutura principal do shell, armazena informações do estado
	t_list	*list; // Lista encadeada que armazenará os comandos
	t_sani	sani; // Estrutura usada para sanitizar a entrada do usuário

	init(&mini, __environ); // Inicializa a estrutura mini, passando as variáveis de ambiente do sistema (__environ)
	while (1)
	{
		signals(1);

		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;

		list = create_list();
		get_input(&mini, &sani, list);
		if (ft_strlen(mini.input) != 0 && mini.input[0] != '|')
		{

			if (!input_validate(&mini) || !quotes_closed(&mini))
				printf("error\n");
			else if (split_cmd(&mini, list) && redir_validate(list))
				run(&mini, list, 0);

		}
		free_reset(&mini, list);
		mini.pipe = 0;
	}
	free_em_all(&mini);
	return (0);
}