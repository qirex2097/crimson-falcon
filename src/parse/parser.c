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

void	parse_cmd_error(t_token *pt)
{
	char	*str;

	if (pt->next)
		str = pt->next->token;
	else
		str = pt->token;
	if (is_pipe(pt))
		ms_perror_syntax("syntax error near unexpected token ", "|");
	else if (ft_strcmp(">", pt->token) == 0 || ft_strcmp("<", pt->token) == 0
		|| ft_strcmp("<<", pt->token) == 0 || ft_strcmp(">>", pt->token) == 0)
	{
		if (pt->next == NULL)
			ms_perror_syntax("syntax error near unexpected token ", "newline");
		else
			ms_perror_syntax("syntax error near unexpected token ", str);
	}
	else
		ms_perror("syntax error");
}

t_token	*parse_cmd_loop(t_cmd *cmd, t_token *pt)
{
	while (pt && !is_delimiter(pt))
	{
		if (is_pipe(pt))
		{
			if (cmd->args[0] == NULL)
				return (pt);
			cmd->next = new_cmd();
			cmd = cmd->next;
			pt = pt->next;
		}
		else if (is_word(pt))
			pt = append_args_element(cmd, pt);
		else if (is_redirect(pt))
			pt = append_redirect_element(cmd, pt);
		else
			return (pt);
	}
	return (NULL);
}

t_node	*parse_cmd(t_token *pt)
{
	t_node	*node;
	t_cmd	*cmd;

	if (is_pipe(pt))
	{
		parse_cmd_error(pt);
		return (NULL);
	}
	node = new_node(ND_SIMPLE_CMD);
	cmd = &node->command;
	pt = parse_cmd_loop(cmd, pt);
	if (pt)
	{
		parse_cmd_error(pt);
		free_node(node);
		return (NULL);
	}
	return (node);
}

t_node	*parse(t_token *tokens)
{
	t_node	head;
	t_node	*node;
	t_token	*pt_table[100];
	int		i;

	split_by_delimiter(tokens, pt_table, 100);
	head.next = NULL;
	node = &head;
	i = 0;
	while (pt_table[i])
	{
		node->next = parse_cmd(pt_table[i]);
		if (node->next == NULL)
		{
			free_node(head.next);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	return (head.next);
}
