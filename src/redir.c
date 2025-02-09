#include "../include/minishell.h"

int	redirect_out(t_mini *mini, t_node *node, int i)
{
	int		flags; // Flags para abertura do arquivo
	char	*file; // Nome do arquivo

	flags = O_WRONLY | O_CREAT; // Define flags básicas: escrita apenas e criar se não existir
	if (node->str[i + 1] == NULL || node->str[i + 1][0] == '>' // Verifica se há erro de sintaxe
		|| node->str[i + 1][0] == '<' || node->str[i + 1][0] == '\0') // como '>' sem arquivo
		return (0); //retorna o erro
	file = ft_strdup(node->str[i + 1]); // Duplica nome do arquivo
	if (!ft_strcmp(node->str[i], ">>")) // Se for redirecionamento append '>>'
	{
		mini->out = open(file, flags | O_APPEND, 0777); // Abre arquivo em modo append
		free(file);
		return (1); // retorna com sucesso
	}
	else if (!ft_strcmp(node->str[i], ">"))  // Se for redirecionamento simples '>'
	{
		mini->out = open(file, flags | O_TRUNC, 0777);// Abre arquivo truncando conteúdo
		free(file);
		return (1); // retorna com sucesso
	}
	free(file);
	return (0);// vai retornar erro ser não for redirecionamento correto
}

void	ft_putstrendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0 && fd != 0) // Se string e fd são válidos
	{
		while (s[i] != '\0') //escreve cada caractere da string
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, "\n", 1); //adiciona uma nova linha no final
	}
}

void	here_doc(char *file, char *eof)
{
	char	*line;  // Linha lida do input
	int		flags; // Flags para abertura do arquivo
	int		fd; // File descriptor

	flags = O_RDWR | O_CREAT | O_TRUNC; // Define flags: leitura/escrita, criar, truncar
	line = ft_strdup(""); //inicializa uma linha vazia
	fd = open(file, flags, 0777); //abre um arquivo temporario
	while (ft_strcmp(line, eof)) //enquando não encontrar o EOF
	{
		free (line);
		line = readline("> ");  // Lê uma linha do usuário
		if (line && ft_strcmp(line, eof)) // Se não for EOF
			ft_putstrendl_fd(line, fd); //escreve uma linha
		else // se for EOF
			break ; // termina
	}
	close(fd); // fecha o arquivo
	free(line); // libera a memoria
}

int	redirect_in(t_mini *mini, t_node *node, int i) // Função que gerencia o redirecionamento de entrada
{
	char	*file; // Variável para armazenar o nome do arquivo em redirecionamento "<"
	char	*eof; // Variável para armazenar o marcador EOF em "here document" "<<"

	if (node->str[i + 1] && !ft_strcmp(node->str[i], "<")) // Verifica se existe um argumento após "<" e se o token é "<"
	{
		file = ft_strdup(node->str[i + 1]); // Duplicação do nome do arquivo para a variável "file"
		mini->in = open(file, O_RDONLY, 0777); // Tenta abrir o arquivo em modo leitura
		if (mini->in == -1) // Se não conseguir abrir o arquivo, retorna erro
		{
			free(file);  // Libera a memória alocada para o nome do arquivo
			return (0); // Retorna 0 indicando falha no redirecionamento
		}
		free(file); // Libera a memória alocada para o nome do arquivo após a abertura bem-sucedida
		return (1); // Retorna 1 indicando sucesso no redirecionamento de entrada
	}
	else if (node->str[i + 1] && !ft_strcmp(node->str[i], "<<")) // Verifica se o token é "<<"
	{
		eof = ft_strdup(node->str[i + 1]); // Duplicação do marcador EOF (fim de arquivo) para a variável "eof"
		here_doc(TMP_FILE, eof); // Chama a função "here_doc" que grava o conteúdo até o EOF em um arquivo temporário
		mini->in = open(TMP_FILE, O_RDONLY, 0777); // Abre o arquivo temporário gerado pelo "here document"
		free(eof); // Libera a memória alocada para o marcador EOF
		return (1); // Retorna 1 indicando sucesso no redirecionamento de entrada
	}
	return (0); // Retorna 0 indicando que nenhum redirecionamento válido foi feito
}