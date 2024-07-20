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

char	*search_path(const char *filename)
{
	char	*path;
	char	*path_copy;

	path = getenv("PATH");
	path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");
	char *full_path = malloc(strlen(path_token) + strlen(filename) + 2); //+2 for '/' and '\0'

    if (!full_path)
	{
		free(path_copy);
		return (NULL);
	}
	while (path_token)
	{
		strcpy(full_path, path_token);
		strcat(full_path, "/");
		strcat(full_path, filename);
		if (access(full_path, X_OK) == 0) 
		{
			free(path_copy);
			return (full_path);
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}


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
	char *full_path;

	rl_outstream = stderr;
	while(1)
	{
		line = readline("minishell$ ");
		if(!line)		
			break;
		//line:full path
		if(line[0] != '/')
		{
			full_path = search_path(line);
			interpret(full_path);
			free(full_path);
		}
		else
		{
			interpret(line);
		}
		free(line);
	}
	exit(status);
}
