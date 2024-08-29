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

int	_exec_builtin_command(t_cmd *cmd, int prev_fd, int *pfd)
{
	int	status;
	int	original_fd[2];

	original_fd[0] = -1;
	original_fd[1] = -1;
	if (prev_fd != -1)
	{
		original_fd[0] = dup(STDIN_FILENO);
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		original_fd[1] = dup(STDOUT_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	if (open_redir_file(cmd->redir_out, cmd->redir_in) < 0)
		return (1);
	status = exec_builtin_command(cmd->args);
	if (original_fd[0] != -1)
		dup2(original_fd[0], STDIN_FILENO);
	if (original_fd[1] != -1)
		dup2(original_fd[1], STDOUT_FILENO);
	return (status);
}
