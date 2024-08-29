/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:34:39 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:34:43 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	exec_cmd(t_cmd *cmd, int prev_fd, int *pfd)
{
	int		wstatus;
	pid_t	pid;

	if (cmd->args[0] == NULL)
		return (0);
	if (is_builtin(cmd->args))
	{
		wstatus = _exec_builtin_command(cmd, prev_fd, pfd);
		return (wstatus);
	}
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
		exec_child_process(cmd, prev_fd, pfd);
	else
	{
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pfd[1]);
		wait(&wstatus);
		return (wstatus);
	}
	return (0);
}

/*
 * *prev_fd = pfd[0]; パイプの読み出し側を更新
 * 子プロセスの戻り値が0以外の場合はパイプの処理を中断する
 */
int	exec_cmd_loop(t_cmd *cmd, int *prev_fd)
{
	int	status;
	int	pfd[2];

	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pfd) < 0)
				fatal_error("pipe");
		}
		status = exec_cmd(cmd, *prev_fd, pfd);
		if (cmd->next)
			*prev_fd = pfd[0];
		if (!WIFEXITED(status))
		{
			if (cmd->next)
				close(*prev_fd);
			break ;
		}
		cmd = cmd->next;
	}
	return (status);
}

/*
 *		prev_fd = -1; //パイプ処理用（読み出し側）
 */
int	exec(t_node *node)
{
	t_cmd	*cmd;
	int		status;
	int		prev_fd;

	status = 0;
	while (node)
	{
		prev_fd = -1;
		cmd = &node->command;
		status = exec_cmd_loop(cmd, &prev_fd);
		node = node->next;
	}
	return (WEXITSTATUS(status));
}
