#include "../include/minishell.h"

void	minipwd(void)
{
	char	wd[1024];

	getcwd(wd, sizeof(wd));
	printf("%s\n", wd);
	g_return = 0; 
}