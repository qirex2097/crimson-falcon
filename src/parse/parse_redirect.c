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

void	append_redirect_node(t_cmd *node, t_redirect *child_node)
{
	t_redirect	**redir_root;
	t_redirect	*p;

	if (node == NULL)
		return ;
	if (child_node->kind == ND_REDIR_HEREDOC)
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

bool	is_redirect(t_token *pt)
{
	if ((ft_strcmp(">", pt->token) == 0 || ft_strcmp("<", pt->token) == 0
			|| ft_strcmp(">>", pt->token) == 0 || ft_strcmp("<<",
				pt->token) == 0) && is_word(pt->next))
		return (true);
	else
		return (false);
}

t_token	*append_redirect_element(t_cmd *node, t_token *tokens)
{
	t_redirect	*redirect_node;

	redirect_node = NULL;
	if (ft_strcmp(">", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_OUT, tokens->next->token);
	else if (ft_strcmp("<", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_IN, tokens->next->token);
	else if (ft_strcmp(">>", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_APPEND, tokens->next->token);
	else if (ft_strcmp("<<", tokens->token) == 0 && is_word(tokens->next))
		redirect_node = new_redirect(ND_REDIR_HEREDOC, tokens->next->token);
	else
		assert_error("append_redirect_element");
	append_redirect_node(node, redirect_node);
	return (tokens->next->next);
}
