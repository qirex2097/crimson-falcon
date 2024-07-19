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

int interpret(char *line, int *stat_loc)
{
    char **argv;
	t_token *tok;

	tok = tokenize(line);
	if (tok->kind == TK_EOF)
		;
	else
	{
		argv = token_list_to_argv(tok);
		//*stat_loc = exec(argv);
		free_argv(argv);
	}
	free_tok(tok);
	return (0);
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

