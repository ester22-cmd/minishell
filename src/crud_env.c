/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:05:22 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 21:05:22 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*create_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->begin = NULL;
	env->end = NULL;
	env->size = 0;
	return (env);
}

t_nodenv	*create_nodenv(char *key, char *content)
{
	t_nodenv	*node;

	node = malloc(sizeof(t_nodenv));
	node->key = ft_strdup(key);
		node->content = ft_strdup(content);
	else
		node->content = ft_strdup("");
	node->next = NULL;
	return (node);
}

void	push_env(t_env *env, char *key, char *content)
{
	t_nodenv	*node;

	node = create_nodenv(key, content);
	if (env->begin == NULL)
	{
		env->begin = node;
		env->end = node;
	}
	else
	{
		env->end->next = node;
		env->end = env->end->next;
	}
	env->size++;
}

void	free_env(t_env **env_ref)
{
	t_env		*env;
	t_nodenv	*node;
	t_nodenv	*aux;

	env = *env_ref;
	node = env->begin;
	aux = NULL;
	while (node != NULL)
	{
		aux = node;
		node = node->next;
		free(aux->key);
		free(aux->content);
		free(aux);
	}
	free(env);
	*env_ref = NULL;
}

void	print_env(t_env *env)
{
	t_nodenv	*node;

	node = env->begin;
	while (node->next != NULL)
	{
		printf("%s=%s\n", node->key, node->content);
		node = node->next;
	}
	printf("%s=%s\n", node->key, node->content);
}
