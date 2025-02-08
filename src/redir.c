#include "../include/minishell.h"
// Define a função redirect_out, que redireciona a saída.
int	redirect_out(t_mini *mini, t_node *node, int i)
{
	int		flags;// Declara uma variável para armazenar as flags de abertura do arquivo
	char	*file;// Declara um ponteiro para a string que armazenará o nome do arquivo.


	flags = O_WRONLY | O_CREAT;// Define as flags para abrir o arquivo em modo de escrita e criá-lo se não existir.
	if (node->str[i + 1] == NULL || node->str[i + 1][0] == '>'
		|| node->str[i + 1][0] == '<' || node->str[i + 1][0] == '\0')// Verifica se o próximo elemento após o operador de redirecionamento é nulo ou se é outro operador ou uma string vazia.
		return (0);
	file = ft_strdup(node->str[i + 1]);// Duplica a string do nome do arquivo a ser redirecionado.
	if (!ft_strcmp(node->str[i], ">>"))// Verifica se o operador de redirecionamento é ">>" (anexar)
	{
		mini->out = open(file, flags | O_APPEND, 0777);// Abre o arquivo com flags para anexar, atribuindo o descritor a mini->out.
		free(file);// Libera a memória alocada para o nome do arquivo.
		return (1);// Retorna 1, indicando sucesso no redirecionamento.
	}
	else if (!ft_strcmp(node->str[i], ">"))// Verifica se o operador de redirecionamento é ">" (substituir)
	{
		mini->out = open(file, flags | O_TRUNC, 0777);// Abre o arquivo com flags para truncar, atribuindo o descritor a mini->out.
		free(file);
		return (1);
	}
	free(file);
	return (0);
}

void	ft_putstrendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0 && fd != 0)// Verifica se a string 's' não é nula e se 'fd' é válido
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);// Escreve o caractere atual no descritor de arquivo
            i++; // Incrementa o contador 'i' para passar ao próximo caractere
			i++;
		}
		write(fd, "\n", 1);// Escreve uma nova linha no descritor de arquivo
	}
}
// Função que cria um "here document" em um arquivo especificado
void	here_doc(char *file, char *eof)
{
	char	*line;// Declaração do ponteiro 'line' para armazenar cada linha lida
	int		flags;// Declaração da variável 'flags' para os parâmetros de abertura do arquivo
	int		fd;// Declaração da variável 'fd' para armazenar o descritor do arquivo


	flags = O_RDWR | O_CREAT | O_TRUNC;// Define os flags para abrir o arquivo em modo leitura/escrita, criando-o se não existir e truncando-o se existir
	line = ft_strdup("");// Inicializa 'line' como uma string vazia (duplicando uma string vazia)
	fd = open(file, flags, 0777);// Abre o arquivo com os flags especificados e permissões de 777
	while (ft_strcmp(line, eof))
	{
		free (line);
		line = readline("> ");
		if (line && ft_strcmp(line, eof))// Se a linha não for nula e não for igual ao delimitador 'eof'
			ft_putstrendl_fd(line, fd);// Escreve a linha no arquivo, seguida de uma nova linha
		else
			break ;
	}
	close(fd);
	free(line);
}
// Função que lida com redirecionamento de entrada.
int	redirect_in(t_mini *mini, t_node *node, int i)
{
	char	*file;// Declaração de um ponteiro para string que irá armazenar o nome do arquivo.
	char	*eof;// Declaração de um ponteiro para string que irá armazenar o delimitador do here-doc.

// Verifica se existe um próximo elemento na string e se o elemento atual é "<".
	if (node->str[i + 1] && !ft_strcmp(node->str[i], "<"))
	{
		file = ft_strdup(node->str[i + 1]);// Duplica a string do próximo elemento.
		mini->in = open(file, O_RDONLY, 0777);// Tenta abrir o arquivo em modo somente leitura.
		if (mini->in == -1)// Verifica se a abertura do arquivo falhou.
		{
			free(file);// Libera a memória alocada para o nome do arquivo.
			return (0);
		}
		free(file);
		return (1);
	}// Verifica se existe um próximo elemento na string e se o elemento atual é "<<". 
	else if (node->str[i + 1] && !ft_strcmp(node->str[i], "<<"))
	{
		eof = ft_strdup(node->str[i + 1]);// Duplica a string do delimitador do here-doc.
		here_doc(TMP_FILE, eof);// Chama a função here_doc para lidar com a entrada do here-doc
		mini->in = open(TMP_FILE, O_RDONLY, 0777);// Tenta abrir o arquivo temporário em modo somente leitura.
        free(eof); // Libera a memória alocada para o delimitado
		free(eof);
		return (1);
	}
	return (0);
}