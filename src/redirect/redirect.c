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

int	apply_redirection(t_redirect *redir, int target_fd)
{
	if (redir->fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
	if (dup2(redir->fd, target_fd) < 0)
	{
		perror("dup2");
		close(redir->fd);
		return (-1);
	}
	close(redir->fd);
	return (0);
}

int	open_redir_in(t_redirect *redir)
{
	int	target_fd;

	if (redir == NULL)
		return (0);
	if (redir->kind == ND_REDIR_HEREDOC)
	{
		redir->fd = create_heredoc(redir->filename);
		target_fd = STDIN_FILENO;
	}
	else if (redir->kind == ND_REDIR_IN && redir->next == NULL)
	{
		redir->fd = open(redir->filename, O_RDONLY);
		target_fd = STDIN_FILENO;
	}
	else
		return (-1);
	return (apply_redirection(redir, target_fd));
}

int	open_redir_out(t_redirect *redir)
{
	int	status;

	status = 0;
	if (redir == NULL)
		return (0);
	if (redir->kind == ND_REDIR_OUT)
	{
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (redir->kind == ND_REDIR_APPEND)
	{
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
		return (-1);
	status = apply_redirection(redir, STDOUT_FILENO);
	if (status != 0)
		return (status);
	status = open_redir_out(redir->next);
	return (status);
}

int	open_redir_file(t_redirect *redir_out, t_redirect *redir_in)
{
	int	status;

	status = 0;
	if (redir_in != NULL)
	{
		while (redir_in->next)
		{
			if (redir_in->kind == ND_REDIR_HEREDOC)
			{
				heredoc_loop(redir_in->filename, -1);
			}
			redir_in = redir_in->next;
		}
		status = open_redir_in(redir_in);
		if (status != 0)
			return (status);
	}
	return (open_redir_out(redir_out));
}
