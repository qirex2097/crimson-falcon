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

void validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int exec_cmd(t_cmd *cmd, int prev_fd)
{
	char *path;
	char **argv = cmd->args;
	int wstatus;
    pid_t pid;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
    if(pid == 0)
    {
		if (prev_fd != -1) {	//パイプの読み出し側が設定されていたら
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (cmd->next) {	//パイプの書き込み側を設定する
			close(cmd->pfd[0]);
			dup2(cmd->pfd[1], STDOUT_FILENO);
			close(cmd->pfd[1]);
		}
		if (open_redir_file(cmd->redirects) < 0) {
			exit(1);//リダイレクトのファイルがオープンできない時は子プロセス終了
		}
		if(strchr(argv[0], '/') == NULL)
			path = search_path(argv[0]);
		else
			path = strdup(argv[0]);
		validate_access(path, argv[0]);//コマンドがない時は子プロセス終了
        execve(path, argv, 0);
		fatal_error("execve");//ここには来ない。
    }
    else
    {
		if (prev_fd != -1) {
			close(prev_fd);	//使わないパイプはクローズする
		}
		if (cmd->next) {
			close(cmd->pfd[1]);
		}

        wait(&wstatus);
		return (WEXITSTATUS(wstatus));
    }
	
	return (0);
}

int exec(t_node *node)
{
	t_cmd *cmd;
	int status = 0;
	int prev_fd;

	while (node)
	{
		prev_fd = -1;	//パイプ処理用（読み出し側）
		cmd = &node->command;
		while (cmd)
		{
			if (cmd->next)
			{
				if (pipe(cmd->pfd) < 0) 	// パイプの次のコマンドがあればパイプを作る
				{
					fatal_error("pipe");
				}
			}
			status = exec_cmd(cmd, prev_fd);
			if (cmd->next)
			{
				prev_fd = cmd->pfd[0];	//パイプの読み出し側を更新
			}
			cmd = cmd->next;
		}
		node = node->next;
	}
	return (status);
}

int interpret(char *line)
{
	char **tokens;
	int status;
	t_node	*node;
	
	tokens = tokenizer(line);//トークンに分割
	if (tokens[0] == NULL) 
	{
		return(0);
	}
	add_history(line);//トークンがなければ履歴に登録しない
	expand(tokens);
	node = parse(tokens);
	status = exec(node);
	free_argv(tokens);
	if (node)
		free_node(node);

    return(status);
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
		{
			status = interpret(line);
		}
		free(line);
	}
	exit(status);
}
