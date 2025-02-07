#include "../include/minishell.h"
// Função que executa o processo filho, recebendo a estrutura principal e o nó do comando atual
void	execute_child(t_mini *mini, t_node *node)
{

	int	i;

	i = 3;
	while (i < 150)// Loop para fechar todos os file descriptors de 3 até 149
	{
		close(i);// Fecha o file descriptor atual
		i++;
	}// Processa o comando atual e atualiza as informações na estrutura mini
	get_cmd(mini, node);
	if (find_path(mini, node->str[0]))// Verifica se encontrou o caminho do executável para o comando
	{
		execve(mini->correct_path, node->str, __environ);// Tenta executar o comando usando execve:
        // - mini->correct_path: caminho completo do executável
        // - node->str: array de argumentos do comando
        // - __environ: variáveis de ambiente do sistema
		perror("error");//imprime mensagem de error
		exit(EXIT_FAILURE);// termina o processo filho com status de falha
	}// Se não houve falha no comando (command_fail == 0)
	if (mini->command_fail == 0)
		exit(g_return);// Sai com o valor da variável global g_return
	else
		exit(0);
}
// Função que executa comandos, recebe como parâmetros uma struct mini, uma lista e um nó
void	execute(t_mini *mini, t_list *list, t_node *node)
{
	int	pid;//variavel para armazenar o ID do processo

	fd_handler(mini);//função que lida com os files descriptors
	if (is_builtin(node))// Se for builtin, executa a função apropriada
		execute_builtin(is_builtin(node), node, mini, list);
	else
	{// Se não for builtin, cria um novo processo
		pid = fork();
		signals(2);// Configura os sinais para o processo filho
		if (pid < 0)
		{
			printf("error\n");// Se fork() falhou, mostra erro
			g_return = 127;
		}
		else if (pid == 0)// Se é processo filho (pid=0), executa o comando
			execute_child(mini, node);
		else
			waitpid(pid, &g_return, WUNTRACED);// Se é processo pai, espera o filho terminar
		if (WIFEXITED(g_return))// Verifica se o processo filho terminou normalmente
			g_return = WEXITSTATUS(g_return);// se sim, define retorno com 0
		else
			g_return = 0;
	}// Restaura os file descriptors padrão de entrada e saída
	dup2(mini->st_out, STDOUT_FILENO);
	dup2(mini->st_in, STDIN_FILENO);
}
// Função que verifica aspas simples e duplas em uma string
// Recebe uma struct mini e uma string como parâmetros
void	verify_quotes(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{// Verifica se o caractere atual é uma aspas simples (S_QUOTE)
		if (str[i] == S_QUOTE)
		{// Se não há nenhuma string aberta (aspas simples ou duplas)
			if (mini->open_s_str == 0 && mini->open_d_str == 0)
				mini->open_s_str = 1;// Se já havia uma string com aspas simples aberta
			else if (mini->open_s_str == 1)// Fecha a string com aspas simples
				mini->open_s_str = 0;
		}
		if (str[i] == D_QUOTE)// Verifica se o caractere atual é uma aspas duplas (D_QUOTE)
		{
			if (mini->open_d_str == 0 && mini->open_s_str == 0)// Se não há nenhuma string aberta (aspas simples ou duplas)
				mini->open_d_str = 1;
			else if (mini->open_d_str == 1)// Se já havia uma string com aspas duplas aberta
				mini->open_d_str = 0;// Fecha a string com aspas duplas
		}
		i++;
	}
}

void	run_cmd(t_mini *mini, t_list *list, t_node *node)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	mini->open_s_str = 0;
	mini->open_d_str = 0;
	if (node != NULL)
	{
		while (node->str[i] && result)
		{
			verify_quotes(mini, node->str[i]);
			result = get_result(mini, node, i);
			i++;
		}
		if (!result)
			printf("error\n");
		else if (result)
		{
			if (mini->in != -1)
				execute(mini, list, node);
		}
	}
}

void	run(t_mini *mini, t_list *list, int i)
{
	t_node	*node;
	int		fd[2];

	node = list->begin;
	mini->st_out = dup(STDOUT_FILENO);
	mini->st_in = dup(STDIN_FILENO);
	while (i < mini->pipe)
	{
		if (pipe(fd) < 0)
			printf("error\n");
		mini->out = fd[1];
		run_cmd(mini, list, node);
		close(fd[1]);
		if (mini->in != 0)
			close(mini->in);
		mini->in = fd[0];
		node = node->next;
		i++;
	}
	if (list->size > 0)
	{
		run_cmd(mini, list, node);
		close(mini->st_out);
		close(mini->st_in);
	}
}