/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:43:22 by kahori            #+#    #+#             */
/*   Updated: 2024/07/21 08:44:37 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	open_redir_file_sub(t_redirect *redir)
{
	int	status;
	int	target_fd;

	status = 0;
	if (redir == NULL)
		return (0);
	if (redir->kind == ND_REDIR_OUT)
	{
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		target_fd = STDOUT_FILENO;
	}
	else if (redir->kind == ND_REDIR_IN)
	{
		redir->fd = open(redir->filename, O_RDONLY);
		target_fd = STDIN_FILENO;
	}
	else if (redir->kind == ND_REDIR_APPEND)
	{
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		target_fd = STDOUT_FILENO;
	}
	else if (redir->kind == ND_REDIR_HEREDOC)
	{
		redir->fd = open_heredoc(redir);
		target_fd = STDIN_FILENO;
	}
	else
	{
		return (-1); // Unknown redirection type
	}
	if (redir->fd < 0)
	{
		perror(redir->filename);
		return (-1); // File Open Error
	}
	if (dup2(redir->fd, target_fd) < 0)
	{
		perror("dup2");
		close(redir->fd);
		return (-1); // Dup2 Error
	}
	close(redir->fd);
	if (redir->kind == ND_REDIR_HEREDOC)
		return (status);
	status = open_redir_file_sub(redir->next);
	return (status);
}

int	open_redir_file(t_redirect *redir, t_redirect *heredoc)
{
	int	status;

	status = 0;
	if (heredoc != NULL)
	{
		status = open_redir_file_sub(heredoc);
		if (status != 0)
			return (status);
	}
	return (open_redir_file_sub(redir));
}
