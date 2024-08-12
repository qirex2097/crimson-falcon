/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:43:22 by kahori            #+#    #+#             */
/*   Updated: 2024/07/21 08:44:37 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

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

void free_redirect(t_redirect *redir)
{
	if (redir->next)
	{
		free_redirect(redir->next);
		free(redir->next);
	}
	free(redir->filename);
}

void free_cmd(t_cmd *cmd)
{
	if (cmd->next) {
		free_cmd(cmd->next);
		free(cmd->next);
	}
	if (cmd->redirects)
	{
		free_redirect(cmd->redirects);
		free(cmd->redirects);
	}
	free_argv(cmd->args);
}

void free_node(t_node *node)
{
	if (node == NULL) 
		return;
	if (node->next) {
		free_node(node->next);
		free(node->next);
	}
	free_cmd(&node->command);
}
/*--------------*/