/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:23:11 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 23:23:14 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../LIBFT/libft.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

# define D_QUOTE '\"'
# define S_QUOTE '\''
# define DELIM "|<>"
# define TMP_FILE "/tmp/here_doc_tmp_file"

/*
** Linked list structure - Commands
*/
typedef struct s_node
{
	char			**str;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*begin;
	t_node	*end;
	t_node	*node;
	size_t	size;
}	t_list;

/*
** Linked list structure - Environment Variables
*/
typedef struct s_nodenv
{
	char			*key;
	char			*content;
	struct s_nodenv	*next;
}	t_nodenv;

typedef struct s_env
{
	t_nodenv	*begin;
	t_nodenv	*end;
	size_t		size;
}	t_env;

typedef struct s_sani
{
	int		i;
	int		j;
	int		s;
	int		d;
}	t_sani;

typedef struct s_hand
{
	int	open;
}	t_hand;

/*
** input -> line read from terminal (raw, no treats)
** input_sanitized -> input ready to work with
** is_open -> int value to check quoting
** env -> pointer to env structure
** list -> pointer to a linked lis
*/
typedef struct s_mini
{
	char	**path;
	char	*input;
	char	*input_sanitized;
	char	*correct_path;
	char	*home;
	int		init_with_arrow;
	int		is_open_s;
	int		is_open_d;
	int		final_s;
	int		final_d;
	int		is_open_s_str;
	int		is_open_d_str;
	int		is_final_s;
	int		is_final_d;
	int		open_s_str;
	int		open_d_str;
	int		pipe;
	int		redir;
	int		out;
	int		in;
	int		st_out;
	int		st_in;
	int		command_fail;
	int		i;
	t_env	*env;
}	t_mini;

extern int	g_return;

/*
** linked list functions
*/
t_list	*create_list(void);
void	push_node(t_list *list, char *str);
void	free_list(t_list **list_ref);
t_env	*create_env(void);
void	push_env(t_env *env, char *key, char *content);
void	free_env(t_env **env_ref);
void	print_env(t_env *env);

/*
** Minishell functions
*/
void	minifree(char **ptr);
void	free_em_all(t_mini *mini);
void	init(t_mini *mini, char **environ);
void	free_reset(t_mini *mini, t_list *list);
void	is_in_quote(char c, t_mini *mini);
int		split_cmd(t_mini *mini, t_list *list);
void	input_sanitizer(t_mini *mini, t_sani *sani);
int		is_builtin(t_node *node);
void	execute_builtin(int builtin, t_node *node, t_mini *mini, t_list *list);
int		find_path(t_mini *mini, char *cmd);
int		is_redirect(char c);
int		redirect_out(t_mini *mini, t_node *node, int i);
int		redirect_in(t_mini *mini, t_node *node, int i);
void	run(t_mini *mini, t_list *list, int i);
void	fd_handler(t_mini *mini);
void	get_cmd(t_mini *mini, t_node *node);
void	get_input(t_mini *mini, t_sani *sani, t_list *list);
int		redir_validate(t_list *list);
int		check_tilda(char *cmd);
void	get_home(t_mini *mini);
char	*copy_path(t_mini *mini, char *cmd, int tilda);
void	get_home(t_mini *mini);
int		len_node(t_mini *mini, char **str);
void	expand_var(t_mini *mini, t_node *node, int i);
void	signals(int signum);
void	get_cmd_builtin(t_mini *mini, t_node *node);
int		is_space(char *str);
int		input_validate(t_mini *mini);
int		quotes_closed(t_mini *mini);
void	is_in_quote_str(char *str, t_mini *mini, int i);
int		is_just_quote(char *str);
int		len_quote(char **str);
char	*transform(t_mini *mini, t_node *node, int i, int j);
int		is_this_quote(char *str);
int		get_result(t_mini *mini, t_node *node, int i);
void	fd_handler(t_mini *mini);
int		is_str_quote(char *str, int open);

/* Builtins */
void	miniexit(t_mini *mini, t_node *node, t_list *list);
void	miniunset(t_env *env, t_node *node, t_nodenv *aux, t_nodenv *prev);
void	minipwd(void);
void	minicd(t_mini *mini, t_node *node);
void	miniecho(t_mini *mini, t_node *node, int i);
void	minienv(t_env *env);
void	miniexport(t_env *env, t_node *node);

#endif
