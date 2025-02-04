#include "../include/minishell.h"s

void	get_env(t_mini *mini, char **environ)
{
	char	**aux;
	int		i;
// Cria uma estrutura de ambiente vazia
	mini->env = create_env();
// Inicializa um contador para percorrer o ambiente
	i = 0;
// Percorre todas as variáveis de ambiente	
	while (environ[i])
	{
// Divide cada entrada de ambiente no caractere '='
// Exemplo: "PATH=/usr/bin" será dividido em ["PATH", "/usr/bin"]
		aux = ft_split(environ[i], '=');
// Adiciona cada variável de ambiente à estrutura do minishell
// Passa a chave (primeiro elemento) e o valor (segundo elemento)
		push_env(mini->env, aux[0], aux[1]);
 // Incrementa o contador
		i++;
// Libera a memória alocada para o array auxiliar
		minifree(aux);
	}
}

void	get_path(t_mini *mini)
{
	char	*path;
	char	*aux;
	int		i;
// Obtém o valor da variável PATH do ambiente do sistema
	path = getenv("PATH");
// Cria uma cópia do caminho para manipulação
	aux = ft_strdup(path);
	if (!aux)
		return ;
// Divide o caminho em um array usando ':' como separador
// Exemplo: "/usr/bin:/bin" será dividido em ["/usr/bin", "/bin"]
	mini->path = ft_split(aux, ':');
//inicializa contador	
	i = 0;
//libera a string auxilar
	free(aux);
//modifica cada caminho adicionando '/' no final
	while (mini->path[i])
	{
// guarda o caminho atual
		aux = mini->path[i];
//concatena '/' ao final de cada caminho
//transforma "usr/bin" em "/usr/bin/"
		mini->path[i] = ft_strjoin(aux, "/");
//incrementar o contador
		i++;
//libera o caminho original		
		free(aux);
	}
}

void	init(t_mini *mini, char **environ)
{
//Carrega todas as variaveis de ambiente
	get_env(mini, environ);
//Obtém os caminhos do sistema
	get_path(mini);
// Obtém o diretório home do usuário
	mini->home = ft_strdup(getenv("HOME"));
// Inicializa diversos flags e estados do minishell:
// Ponteiro para caminho correto (iniciado como NULL)
	mini->correct_path = NULL;
// Flags para controle de aspas simples e duplas
	mini->is_open_s = 0; // Aspas simples abertas
	mini->is_open_d = 0; // Aspas duplas abertas
	mini->is_open_d_str = 0; // String com aspas duplas abertas
	mini->is_open_s_str = 0; // String com aspas simples abertas
	mini->is_final_s = 0; // Aspas simples fechadas
	mini->is_final_d = 0; // Aspas duplas fechadas
// Flag para inicialização com redirecionador
	mini->init_with_arrow = 0;
// Flags para pipes e redirecionamentos
	mini->pipe = 0;
	mini->redir = 0;
// Status de falha de comando (inicialmente 1)
	mini->command_fail = 1;
// Variável global de retorno
	g_return = 0;
}
