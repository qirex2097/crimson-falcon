/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:35:42 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:35:45 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

t_token	*skip_delimiter(t_token *tokens)
{
	t_token	*pt;

	pt = tokens;
	while (is_delimiter(pt))
		pt = pt->next;
	return (pt);
}

void	split_by_delimiter(t_token *tokens, t_token **table, int table_max)
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
