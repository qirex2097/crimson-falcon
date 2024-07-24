#include "minishell.h"
typedef struct s_token	t_token;


// char	*search_path(const char *filename)
// {
// 	char	*path;
// 	char	*path_copy;

// 	path = getenv("PATH");
// 	path_copy = strdup(path);
//     char *path_token = strtok(path_copy, ":");
// 	char *full_path = malloc(strlen(path_token) + strlen(filename) + 2); //+2 for '/' and '\0'

//     if (!full_path)
// 	{
// 		free(path_copy);
// 		return (NULL);
// 	}
// 	while (path_token)
// 	{
// 		strcpy(full_path, path_token);
// 		strcat(full_path, "/");
// 		strcat(full_path, filename);
// 		if (access(full_path, X_OK) == 0) 
// 		{
// 			free(path_copy);
// 			printf("full_path:%s\n", full_path);
// 			return (full_path);
// 		}
// 		path_token = strtok(NULL, ":");
// 	}
// 	free(path_copy);
// 	return ("error");
// }

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
	while (*value)
	{
		// /bin:/usr/bin
		//     ^
		//     end
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			strlcpy(path, value, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			char	*dup;

			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

int interpret(char *line)
{
	char *path;
	char **argv = tokenizer(line);
	if(argv == NULL)
	{
		free(argv);
		exit (1);
	}
	// printf("argv[0]:%s\n", argv[0]);
	// printf("path:%s\n", path);

    pid_t pid = fork();
    if(pid == 0)
    {
		if(strchr(argv[0], '/') == NULL)
			path = search_path(argv[0]);
		else
			path = strdup(argv[0]);
        execve(path, argv, 0);
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
	//char *full_path;

	rl_outstream = stderr;
	while(1)
	{
		line = readline("minishell$ ");
		if(!line)		
			break;
		//line:full path0
		if(*line)
			add_history(line);
		interpret(line);
		free(line);
	}
	exit(status);
}
