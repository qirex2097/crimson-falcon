#include "minishell.h"
typedef struct s_token	t_token;


/*------free-------*/
void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
		free(tok->word);
	free_tok(tok->next);
	free(tok);
}

void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
/*--------------*/

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
        wait(0);
    }
    return 0;
}

int	main()
{
	char	*line;
	int	status = 0;

	rl_outstream = stderr;
	while(1)
	{
		line = readline("minishell$ ");
		
		if(!line)		
			break ;
		if(*line)
		{
			add_history(line);
		}
		interpret(line, &status);
		free(line);
	}
	exit(status);
}

