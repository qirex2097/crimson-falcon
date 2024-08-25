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

t_node	*parse_cmd(t_token *tokens)
{
	t_token	*pt;
	t_node	*node;
	t_cmd	*cmd;

	pt = tokens;
	if (is_pipe(pt))
	{
		ms_perror("syntax error near unexpected token `|'");
		return (NULL);
	}
	node = new_node(ND_SIMPLE_CMD);
	cmd = &node->command;
	while (pt && !is_delimiter(pt))
	{
		if (is_pipe(pt))
		{
			if (pt->next == NULL || !is_word(pt->next))
			{
				perror("parse error");
				free_node(node);
				return (NULL);
			}
			cmd->next = new_cmd();
			cmd = cmd->next;
			pt = pt->next;
		}
		else if (is_word(pt))
		{
			pt = append_args_element(cmd, pt);
		}
		else
		{
			pt = append_redirect_element(cmd, pt);
		}
	}
	return (node);
}

t_token	*skip_delimiter(t_token *tokens)
{
	t_token	*pt;

	pt = tokens;
	while (is_delimiter(pt))
		pt = pt->next;
	return (pt);
}

void	split_command_line(t_token *tokens, t_token **table, int table_max)
{
	int		i;
	t_token	*pt;

	pt = skip_delimiter(tokens);
	i = 0;
	table[i] = pt;
	i++;
	while (pt && i < table_max - 1)
	{
		while (pt && !is_delimiter(pt))
		{
			pt = pt->next;
		}
		pt = skip_delimiter(pt);
		table[i] = pt;
		i++;
	}
	table[i] = NULL;
	return ;
}

t_node	*parse(t_token *tokens)
{
	t_node	head;
	t_node	*p;
	t_token	*pt_table[100];
	int		i;

	split_command_line(tokens, pt_table, 100);
	head.next = NULL;
	p = &head;
	i = 0;
	while (pt_table[i])
	{
		p->next = parse_cmd(pt_table[i]);
		if (p->next == NULL)
		{
			free_node(head.next);
			return (NULL);
		}
		p = p->next;
		i++;
	}
	return (head.next);
}
