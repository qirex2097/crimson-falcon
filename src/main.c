#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int interpret(char *line)
{
    char *argv[] = {line, NULL};
    pid_t pid = fork();

    if(pid == 0)
    {
        execve(line, argv, 0);
        exit(0);
    }
    else
    {
		//TO DO:waitの挙動確認
        wait(0);
    }
    return 0;
}

int	main()
{
	char	*line;

	// rl_outstream = stderr;
	while(1)
	{
		line = readline("minishell$ ");
		
		if(!line)		
			break ;
		if(*line)
		{
			//add_history(line);
			interpret(line);
		}
		free(line);
	}
	exit(0);
}

