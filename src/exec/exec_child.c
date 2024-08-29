/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*
 * パイプの読み出し側が設定されていたら dup2(prev_fd, STDIN_FILENO)
 * パイプの書き込み側を設定する dup2(pfd[1], STDOUT_FILENO)
 */
void	prepare_pipe(t_cmd *cmd, int prev_fd, int *pfd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
}

/*
 * リダイレクトのファイルがオープンできない時は子プロセス終了
 * コマンドがない時は子プロセス終了
 */
void	exec_child_process(t_cmd *cmd, int prev_fd, int *pfd)
{
	char	**argv;
	char	**env_array;
	char	*path;

	argv = cmd->args;
	reset_signal();
	prepare_pipe(cmd, prev_fd, pfd);
	if (open_redir_file(cmd->redir_out, cmd->redir_in) < 0)
	{
		exit(1);
	}
	if (ft_strchr(argv[0], '/') == NULL)
		path = search_path(argv[0]);
	else
		path = ft_strdup(argv[0]);
	if (is_directory(path))
		err_exit(argv[0], "is a directory", 126);
	if (is_command_not_found(path))
		err_exit(argv[0], "command not found", 127);
	env_array = create_env_array(g_env_root.next);
	execve(path, argv, env_array);
	fatal_error("execve");
}
