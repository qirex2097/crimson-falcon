#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

void sigint_handler(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    return;
}

void sigquit_handler(int sig)
{
    (void)sig;
    return;
}

int main(int argc, char **argv)
{
    char *line;
    
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    
    while (1)
    {
        line = readline("$ ");
        if (!line)
            break;
        printf("You entered: %s\n", line);
        free(line);
    }
}
