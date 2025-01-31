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
}	t_mini;

extern int	g_return;
