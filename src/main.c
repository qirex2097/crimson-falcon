#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main()
{
	char	*line;

	// rl_outstream = stderr;
	while(1)
	{
		line = readline("minishell$ ");
		if(!line)		
			break ;
		printf("line:%s\n", line);
		if(*line)
		{
			//add_history(line);
		}
		free(line);
	}
	exit(0);
}

