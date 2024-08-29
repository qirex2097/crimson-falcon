/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:35:33 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:35:37 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	initialize_cmd(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * TOKEN_MAX);
	if (cmd->args == NULL)
		fatal_error("malloc error");
	cmd->args[0] = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->next = NULL;
	return ;
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		fatal_error("malloc error");
	initialize_cmd(cmd);
	return (cmd);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		fatal_error("malloc error");
	node->kind = kind;
	node->next = NULL;
	initialize_cmd(&node->command);
	return (node);
}

t_redirect	*new_redirect(t_node_kind kind, char *filename)
{
	t_redirect	*node;

	node = malloc(sizeof(t_redirect));
	if (node == NULL)
		fatal_error("malloc error");
	node->kind = kind;
	node->filename = ft_strdup(filename);
	node->fd = -1;
	node->next = NULL;
	return (node);
}
