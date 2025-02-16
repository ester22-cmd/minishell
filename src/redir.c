/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:18:35 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 23:18:35 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_out(t_mini *mini, t_node *node, int i)
{
	int		flags;
	char	*file;


	flags = O_WRONLY | O_CREAT;
	if (node->str[i + 1] == NULL || node->str[i + 1][0] == '>'
		|| node->str[i + 1][0] == '<' || node->str[i + 1][0] == '\0')
		return (0);
	file = ft_strdup(node->str[i + 1]);
	if (!ft_strcmp(node->str[i], ">>"))
	{
		mini->out = open(file, flags | O_APPEND, 0777);
		free(file);
		return (1);
	}
	else if (!ft_strcmp(node->str[i], ">"))
	{
		mini->out = open(file, flags | O_TRUNC, 0777);
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
	if (s != 0 && fd != 0)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, "\n", 1);
	}
}

void	here_doc(char *file, char *eof)
{
	char	*line;
	int		flags;
	int		fd;


	flags = O_RDWR | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(file, flags, 0777);
	while (ft_strcmp(line, eof))
	{
		free (line);
		line = readline("> ");
		if (line && ft_strcmp(line, eof))
			ft_putstrendl_fd(line, fd);
		else
			break ;
	}
	close(fd);
	free(line);
}

int	redirect_in(t_mini *mini, t_node *node, int i)
{
	char	*file;
	char	*eof;

	if (node->str[i + 1] && !ft_strcmp(node->str[i], "<"))
	{
		file = ft_strdup(node->str[i + 1]);
		mini->in = open(file, O_RDONLY, 0777);
		if (mini->in == -1)
		{
			free(file);
			return (0);
		}
		free(file);
		return (1);
	}
	else if (node->str[i + 1] && !ft_strcmp(node->str[i], "<<"))
	{
		eof = ft_strdup(node->str[i + 1]);
		here_doc(TMP_FILE, eof);
		mini->in = open(TMP_FILE, O_RDONLY, 0777);
        free(eof);
		free(eof);
		return (1);
	}
	return (0);
}