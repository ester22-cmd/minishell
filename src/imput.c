#include "../includes/minishell.h"

void init_readline(void)
{
   using_history();
   rl_catch_signals = 0;
}

void handle_sigint(int sig)
{
   (void)sig;
   printf("\n");
   rl_on_new_line();
   rl_replace_line("", 0);
   rl_redisplay();
}

// int main(void)
// {
//    char *input;

//    init_readline();
//    signal(SIGINT, handle_sigint);
//    signal(SIGQUIT, SIG_IGN);

//    while (1)
//    {
//        input = readline("minishell> ");
//        if (!input)  // Ctrl+D
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*input)  // Se linha não vazia
//            add_history(input);
           
//        // Processar input aqui
       
//        free(input);
//    }
//    clear_history();
//    return (0);
// }

char	*get_input(void)
{
    char	*line;
    
    // Exibe o prompt
    display_prompt();
    
    // Lê a linha usando readline
    line = readline("");
    if (!line)
    {
        // Ctrl+D (EOF) foi pressionado
        printf("exit\n");
        exit(0);
    }
    
    // Se a linha não estiver vazia, adiciona ao histórico
    if (*line)
        add_history(line);
        
    return (line);
}

void	display_prompt(void)
{
    char	cwd[1024];
    char	*prompt;
    
    // Obtém o diretório atual
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        prompt = ft_strjoin("minihell:", cwd);
        prompt = ft_strjoin(prompt, "$ ");
        printf("%s", prompt);
        free(prompt);
    }
    else
    {
        // Caso não consiga obter o diretório, usa um prompt padrão
        printf("minihell$ ");
    }
}

void	init_input(void)
{
    // Configura o tratamento de sinais
    signal(SIGINT, handle_sigint);  // Ctrl+C
    signal(SIGQUIT, SIG_IGN);       // Ctrl+\
    
    // Inicializa o histórico
    using_history();
}

void	handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	cleanup_input(void)
{
    // Limpa o histórico ao finalizar
    clear_history();
}