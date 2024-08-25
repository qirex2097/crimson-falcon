/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:45:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/31 08:27:39 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

char	**get_operators(void)
{
	static char	*operators[8];

	operators[0] = ">>";
	operators[1] = "<<";
	operators[2] = ">";
	operators[3] = "<";
	operators[4] = ";";
	operators[5] = "|";
	operators[6] = " ";
	operators[7] = NULL;
	return (operators);
}

bool	is_command_line_operator(char *line)
{
	char	**operators;
	int		i;

	operators = get_operators();
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(operators[i], line, ft_strlen(operators[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

t_token	*tokenizer(char *line)
{
	char	*start;
	char	*curr;
	t_token	head;
	t_token	*p;

	head.next = NULL;
	p = &head;
	curr = line;
	while (*curr)
	{
		curr = skip_blank(curr);
		if (*curr == '\0')
			break ;
		start = curr;
		curr = skip_token(curr);
		if (curr == NULL) //',"を閉じていない場合
		{
			free_tokens(head.next);
			return (NULL);
		}
		p->next = append_token(start, curr); // tokenをcopyして格納する
		p = p->next;
	}
	return (head.next);
}
