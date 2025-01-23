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

int main(void)
{
   char *input;

   init_readline();
   signal(SIGINT, handle_sigint);
   signal(SIGQUIT, SIG_IGN);

   while (1)
   {
       input = readline("minishell> ");
       if (!input)  // Ctrl+D
       {
           printf("exit\n");
           break;
       }
       if (*input)  // Se linha não vazia
           add_history(input);
           
       // Processar input aqui
       
       free(input);
   }
   clear_history();
   return (0);
}