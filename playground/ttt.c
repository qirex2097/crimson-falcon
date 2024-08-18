#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char	*line;

	rl_outstream = stderr;
	while(1)
	{
		line = readline("m42$ ");
		if(!line)		
			break; 
		if(*line) 
		{
            printf("%s$\n", line);
		}
		free(line);
	}
    return 0;
}
