#include "../include/minishell.h"

void	expand_var(t_mini *mini, t_node *node, int i)
{
	char		*holder;

	holder = transform(mini, node, i, 0);
	if (holder != NULL)
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(holder);
		free(holder);
	}
	else
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(" ");
	}
}