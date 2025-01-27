#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

// Estruturas básicas
typedef struct	s_token {
	char	*value;
	int		type;
	struct s_token *next;
}   t_token;

typedef struct s_command {
	char	**args;
	char	*input_file;
	char	*output_file;
	int		append_mode;
	struct s_command *next;
} t_command;

// Protótipos das funções principais
void		setup_signals(void);
t_token		*tokenize(char *line);
t_command	*parse_commands(t_token *tokens);
int			execute_pipeline(t_command *cmd);

#endif
