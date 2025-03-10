/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:20:37 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 23:20:37 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	execute_child(t_mini *mini, t_node *node)
{
	int	i;

	i = 3;
	while (i < 150)
	{
		close(i);
		i++;
	}
	get_cmd(mini, node);
	if (find_path(mini, node->str[0]))
	{
		execve(mini->correct_path, node->str, __environ);
		perror("error");
		exit(EXIT_FAILURE);
	}
	if (mini->command_fail == 0)
		exit(returnStatus(-1));
	else
		exit(0);
}

void	execute(t_mini *mini, t_list *list, t_node *node)
{
	int	pid;
	int	status;

	fd_handler(mini);
	if (is_builtin(node))
		execute_builtin(is_builtin(node), node, mini, list);
	else
	{
		pid = fork();
		signals(2);
		if (pid < 0)
		{
			printf("error\n");
			returnStatus(127);
		}
		else if (pid == 0)
			execute_child(mini, node);
		else
			waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			returnStatus(WEXITSTATUS(status));
		else
			returnStatus(0);
	}
	dup2(mini->st_out, STDOUT_FILENO);
	dup2(mini->st_in, STDIN_FILENO);
}

void	verify_quotes(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE)
		{
			if (mini->open_s_str == 0 && mini->open_d_str == 0)
				mini->open_s_str = 1;
			else if (mini->open_s_str == 1)
				mini->open_s_str = 0;
		}
		if (str[i] == D_QUOTE)
		{
			if (mini->open_d_str == 0 && mini->open_s_str == 0)
				mini->open_d_str = 1;
			else if (mini->open_d_str == 1)
				mini->open_d_str = 0;
		}
		i++;
	}
}

void	run_cmd(t_mini *mini, t_list *list, t_node *node)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	mini->open_s_str = 0;
	mini->open_d_str = 0;
	if (node != NULL)
	{
		while (node->str[i] && result)
		{
			verify_quotes(mini, node->str[i]);
			result = get_result(mini, node, i);
			i++;
		}
		if (!result)
			printf("error\n");
		else if (result)
		{
			if (mini->in != -1)
				execute(mini, list, node);
		}
	}
}

void	run(t_mini *mini, t_list *list, int i)
{
	t_node	*node;
	int		fd[2];

	node = list->begin;
	mini->st_out = dup(STDOUT_FILENO);
	mini->st_in = dup(STDIN_FILENO);
	while (i < mini->pipe)
	{
		if (pipe(fd) < 0)
			printf("error\n");
		mini->out = fd[1];
		run_cmd(mini, list, node);
		close(fd[1]);
		if (mini->in != 0)
			close(mini->in);
		mini->in = fd[0];
		node = node->next;
		i++;
	}
	if (list->size > 0)
	{
		run_cmd(mini, list, node);
		close(mini->st_out);
		close(mini->st_in);
	}
}
