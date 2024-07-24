/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:48:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/24 22:05:25 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
typedef struct s_token	t_token;


// char	*search_path(const char *filename)
// {
// 	char	*path;
// 	char	*path_copy;

// 	path = getenv("PATH");
//     if(path == NULL)
//     {
//         return (NULL);
//     }
// 	path_copy = strdup(path);
//     if(path_copy == NULL)
//     {
//         return (NULL);
//     }
//     char *path_token = strtok(path_copy, ":");
//     if(path_token == NULL)
//     {
//         free(path_copy);
//         return (NULL);
//     }
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
// 			return (full_path);
// 		}
// 		path_token = strtok(NULL, ":");
// 	}
//     free(full_path);
// 	free(path_copy);
// 	return (NULL);
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
        if(*line)
            add_history(line);
		if(strchr(line, '/') == NULL)
		{
			full_path = search_path(line);
			if(full_path == NULL)
			{
				status = 127;
			}
			else
			{
				interpret(full_path);
				free(full_path);
			}
		}
		else
		{
			interpret(line);
		}
		free(line);
	}
	exit(status);
}