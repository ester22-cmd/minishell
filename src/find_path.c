#include "../include/minishell.h"

int	check_tilda(char *cmd) //Conta quantos caracteres ~ existem em uma string
{
	int	i; // índice para percorrer string
	int	j; // contador de ~

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
			j++;
		i++;
	}
	return (j); // return: número de ~ encontrados
}

char	*check_home(t_mini *mini, char *cmd) //Processa um comando que contém ~ expandindo para o path home
{
	int		tilda;

	tilda = check_tilda(cmd); // Conta quantos ~ existem
	get_home(mini); // Atualiza o valor de HOME
	return (copy_path(mini, cmd, tilda)); //return: nova string com ~ expandido
}

char	**blabla(t_mini *mini) //Obtém e divide o PATH do ambiente em um array de strings
{
	char		**path; // Array de paths
	char		*aux; // String auxiliar
	t_nodenv	*node; // Nó atual do ambiente

	node = mini->env->begin; // Procura a variável PATH no ambiente
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, "PATH"))
		{ // Copia o conteúdo do PATH
			aux = ft_strdup(node->content);
			// Divide nos ':'
			path = ft_split(aux, ':');
			free(aux);
			return (path);
		}
		node = node->next;
	}
	path = NULL;
	return (path); //return: array de diretórios do PATH ou NULL
}

int	verify_path(t_mini *mini, char *cmd, char *path, int i) // Verifica se um comando existe em algum dos diretórios do PATH
{
	char	**holder; // Array de paths
	char	*aux; // String auxiliar

	// Obtém array de diretórios do PATH
	holder = blabla(mini);
	if (holder != NULL) // Para cada diretório
	{
		while (holder[i])
		{// Para cada diretório
			aux = holder[i];
			// Adiciona '/' no final
			holder[i] = ft_strjoin(aux, "/");
			// Concatena com o comando
			path = ft_strjoin(holder[i], cmd);
			free(aux);
			if (!access(path, F_OK))  // Verifica se o arquivo existe
			{
				mini->correct_path = ft_strdup(path); // Se existe, salva o path correto
				free(path);
				minifree(holder);
				return (1);
			}
			free(path);
			i++;
		}
	}
	minifree(holder);
	return (0); //return: 1 se encontrou, 0 se não
}

/*
** function that searches the right executable in every path available
*/
int	find_path(t_mini *mini, char *cmd) //Procura o executável correto em todos os paths disponíveis
{
	int	tilda;

	if (!cmd)
		return (0);
	if (verify_path(mini, cmd, NULL, 0)) // Tenta encontrar nos diretórios do PATH
		return (1);
	tilda = check_tilda(cmd); // Verifica se tem ~
	if (tilda) // Verifica se tem ~
		cmd = check_home(mini, cmd);
	if (!access(cmd, F_OK)) // Verifica se o arquivo existe diretamente
	{
		mini->correct_path = ft_strdup(cmd);
		return (1);
	}
	if (ft_strlen(cmd) > 0) // Se o comando não foi encontrado
	{
		printf("error command not found\n");
		mini->command_fail = 0;
		g_return = 127;
	}
	if (tilda)
		free(cmd);
	return (0); //return: 1 se encontrou, 0 se não 
}