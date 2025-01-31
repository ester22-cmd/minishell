#include "../include/minishell.h"

void	minicd(t_mini *mini, t_node *node)
{
	t_nodenv	*env;
	char		*home;

	env = mini->env->begin;
	home = NULL;
	if (node->str[1])
		g_return = chdir(node->str[1]);
	else
	{
		while (env != NULL)
		{
			if (!ft_strcmp(env->key, "HOME"))
				home = ft_strdup(env->content);
			env = env->next;
		}
		if (home != NULL)
		{
			chdir(home);
			free(home);
		}
	}
	if (g_return < 0)
		printf("cd: no such file or directory\n");
	if (g_return < 0)
		g_return = 1;
}