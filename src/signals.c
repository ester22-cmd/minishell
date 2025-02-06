#include "../include/minishell.h"

void	handler(int signum)
{// Se o sinal recebido for SIGINT (Ctrl+C)
	if (signum == SIGINT)
	{
		g_return = 130;
		write(1, "\n", 1);
	}// Se o sinal recebido for SIGQUIT (Ctrl+\)
	if (signum == SIGQUIT)
	{
		g_return = 131;
		write(1, "\n", 1);
		printf("Quit (core dumped)\n");
	}
}

// Função handler_main que trata sinais específicos para o prompt principal
void	handler_main(int signum)
{
	g_return = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signum;
}

void	signals(int signum)
{// Modo 1: configuração para o prompt principal
	if (signum == 1)
	{
		signal(SIGINT, handler_main);
		signal(SIGQUIT, SIG_IGN);
	}// Modo 2: configuração para processos filhos
	if (signum == 2)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
	}
}