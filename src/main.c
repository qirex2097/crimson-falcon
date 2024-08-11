/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO search_pathを書き換える！
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
		if (end) {
			strncpy(path, value, end - value);
		} else {
			strncpy(path, value, PATH_MAX - 1);
			path[PATH_MAX - 1] = '\0';
		}
		strncat(path, "/", PATH_MAX - 1);
		path[PATH_MAX - 1] = '\0';
		strncat(path, filename, PATH_MAX - 1);
		path[PATH_MAX - 1] = '\0';
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

int exec_cmd(t_cmd *node)
{
	char *path;
	char **argv = node->args;
	int wstatus;
    pid_t pid;

	pid = fork();
    if(pid == 0)
    {
		if(strchr(argv[0], '/') == NULL)
			path = search_path(argv[0]);
		else
			path = strdup(argv[0]);
        execve(path, argv, 0);
		fatal_error("execve");
    }
    else
    {
        wait(&wstatus);
		return (WEXITSTATUS(wstatus));
    }
	
	return (0);
}

int exec_node(t_cmd *cmd)
{
	int backup_fd[2] = {-1, -1};
	int status = 0;

	while (cmd) {
		backup_fd[0] = -1;
		backup_fd[1] = -1;
		if (open_redir_file(cmd->redirects, backup_fd) < 0) {
			return -1;
		}
		if (do_redirect(cmd->redirects) < 0) {
			return -1;
		}
		status = exec_cmd(cmd);
		close_redirect_files(cmd->redirects);
		reset_redirect(backup_fd);
		cmd = cmd->consumer;//次はパイプの右側のコマンド
	}
	return (status);
}

int exec(t_node *node)
{
	int status;
	while (node)
	{
		status = exec_node(&node->command);
		node = node->next;
	}
	return (status);
}

int interpret(char *line)
{
	char **tokens;
	int status;
	t_node	*node;
	
	tokens = tokenizer(line);
	if(tokens == NULL)
		exit (EXIT_FAILURE);
	expand(tokens);
	node = parse(tokens);
	status = exec(node);
	free_argv(tokens);

    return status;
}

int	main()
{
	char	*line;
	int	status = 0;

	rl_outstream = stderr;
	while(1)
	{
		line = readline("m42$ ");
		if(!line)		
			break;
		if(*line)
			add_history(line);
		status = interpret(line);
		free(line);
	}
	exit(status);
}
