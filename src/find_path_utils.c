#include "../include/minishell.h"

void	get_home(t_mini *mini) //Obtém e atualiza o valor da variável HOME no minishell
{
	t_nodenv	*env; // Ponteiro para percorrer a lista de variáveis de ambiente

	env = mini->env->begin; // Começa do início da lista
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, "HOME")) // Procura pela variável HOME
			break ;
		env = env->next;
	}
	if (env->content) // Se encontrou e tem conteúdo
	{
		free(mini->home); // Libera o valor antigo de home
		mini->home = ft_strdup(env->content); // Atualiza com uma cópia do novo valor
	}
}

char	*copy_string(t_mini *mini, char *cmd, int len_home, int tilda) // Copia uma string substituindo ~ pelo valor de HOME
{
	char	*str; // Nova string
	int		i; // Índice para string original
	int		j; // Índice para nova string
	int		k; // Índice para path home

	i = 0;
	j = 0;
	k = 0;
	// Aloca espaço para nova string (tamanho home + comando - número de ~)
	str = malloc (sizeof(char) * len_home + ft_strlen(cmd) + 1 - tilda);
	while (cmd[i]) // Percorre a string original
	{
		if (cmd[i] != '~')
		// Se não for ~, copia normalmente
			str[j++] = cmd[i++];
		else
		{
			if (i != 0) // Se for ~, mas não no início
				k++;
			while (mini->home[k])  // Copia o path home
				str[j++] = mini->home[k++];
			k = 0;
			i++;
		}
	}
	str[j] = '\0';
	return (str); //@return: nova string com ~ expandido
}

char	*copy_path(t_mini *mini, char *cmd, int tilda) //Prepara e realiza a cópia de um path expandindo
{
	char	*aux; // String auxiliar para resultado
	int		len_home; // Comprimento do path home
	int		i; // Índice auxiliar

	len_home = ft_strlen(mini->home); // Obtém comprimento do path home
	i = 0;
	if (cmd[i] == '~') //Se começa com ~, incrementa len_home
		len_home++;
	aux = copy_string(mini, cmd, len_home, tilda); //Copia a string fazendo as substituições
	return (aux);
}