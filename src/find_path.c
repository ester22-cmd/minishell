#include "../include/minishell.h"

int	check_tilda(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
			j++;
		i++;
	}
	return (j);
}

char	*check_home(t_mini *mini, char *cmd)
{
	int		tilda;

	tilda = check_tilda(cmd);
	get_home(mini);
	return (copy_path(mini, cmd, tilda));
}

char	**blabla(t_mini *mini)
{
	char		**path;
	char		*aux;
	t_nodenv	*node;

	node = mini->env->begin;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, "PATH"))
		{
			aux = ft_strdup(node->content);
			path = ft_split(aux, ':');
			free(aux);
			return (path);
		}
		node = node->next;
	}
	path = NULL;
	return (path);
}

int	verify_path(t_mini *mini, char *cmd, char *path, int i)
{
	char	**holder;
	char	*aux;

	holder = blabla(mini);
	if (holder != NULL)
	{
		while (holder[i])
		{
			aux = holder[i];
			holder[i] = ft_strjoin(aux, "/");
			path = ft_strjoin(holder[i], cmd);
			free(aux);
			if (!access(path, F_OK))
			{
				mini->correct_path = ft_strdup(path);
				free(path);
				minifree(holder);
				return (1);
			}
			free(path);
			i++;
		}
	}
	minifree(holder);
	return (0);
}

/*
** function that searches the right executable in every path available
*/
int	find_path(t_mini *mini, char *cmd)
{
	int	tilda;

	if (!cmd)
		return (0);
	if (verify_path(mini, cmd, NULL, 0))
		return (1);
	tilda = check_tilda(cmd);
	if (tilda)
		cmd = check_home(mini, cmd);
	if (!access(cmd, F_OK))
	{
		mini->correct_path = ft_strdup(cmd);
		return (1);
	}
	if (ft_strlen(cmd) > 0)
	{
		printf("error command not found\n");
		mini->command_fail = 0;
		g_return = 127;
	}
	if (tilda)
		free(cmd);
	return (0);
}