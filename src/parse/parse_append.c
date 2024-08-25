/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:16:43 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:52:00 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

t_token	*append_pipe_element(t_cmd *cmd, t_token *pt)
{
	if (pt->next == NULL || !is_word(pt->next))
		return (NULL);
	cmd->next = new_cmd();
	cmd = cmd->next;
	pt = pt->next;
	return (pt);
}

void	append_redirect_node(t_cmd *node, t_redirect *child_node)
{
	t_redirect	**redir_root;
	t_redirect	*p;

	if (node->kind == ND_REDIR_HEREDOC)
		redir_root = &node->heredoc;
	else
		redir_root = &node->redirects;
	if (*redir_root == NULL)
	{
		*redir_root = child_node;
	}
	else
	{
		p = *redir_root;
		while (p->next)
			p = p->next;
		p->next = child_node;
	}
}

t_token	*append_redirect_element(t_cmd *node, t_token *tokens)
{
	t_redirect	*redirect_node;

	if (ft_strcmp(">", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_OUT, tokens->next->token);
	else if (ft_strcmp("<", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_IN, tokens->next->token);
	else if (ft_strcmp(">>", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_APPEND, tokens->next->token);
	else if (ft_strcmp("<<", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_HEREDOC, tokens->next->token);
	else
	{
		perror("parse error");
		return (NULL);
	}

	append_redirect_node(node, redirect_node);
	return (tokens->next->next);
}

t_token	*append_args_element(t_cmd *node, t_token *token)
{
	int	i;

	i = 0;
	while (node->args[i] && i < TOKEN_MAX - 1) // node->args のインデックスのチェック
		i++;
	node->args[i] = ft_strdup(token->token);
	node->args[i + 1] = NULL;
	return (token->next);
}
