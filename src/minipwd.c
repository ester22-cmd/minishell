#include "../include/minishell.h"

void	minipwd(void)
{
	char	wd[1024]; // Cria um vetor de caracteres 'wd' com capacidade para armazenar até 1024 caracteres.

	getcwd(wd, sizeof(wd)); // Obtém o diretório de trabalho atual e armazena no vetor 'wd'. A função getcwd preenche 'wd' com o caminho absoluto do diretório de trabalho.
	printf("%s\n", wd); // Imprime o caminho do diretório de trabalho atual (armazenado em 'wd').
	g_return = 0; 
    g_return = 0;  // Define o valor de 'g_return' como 0 (provavelmente um indicador global de status de execução, definindo sucesso).
}