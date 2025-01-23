#include "../includes/minishell.h"

int main(void)
{
    char *line;

    setup_signals();
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break;
        add_history(line);
        // Implementar: tokenização e execução
        free(line);
    }
    return (0);
}
