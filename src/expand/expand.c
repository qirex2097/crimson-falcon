/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

void	remove_quotes_init(int *i, int *j, bool *in_single_quotes,
		bool *in_double_quotes)
{
	*i = 0;
	*j = 0;
	*in_single_quotes = false;
	*in_double_quotes = false;
}

bool	quotes_check(char ch, bool *in_single_quotes, bool *in_double_quotes)
{
	if (ch == '\'' && !*in_double_quotes)
	{
		*in_single_quotes = !*in_single_quotes;
		return (true);
	}
	else if (ch == '"' && !*in_single_quotes)
	{
		*in_double_quotes = !*in_double_quotes;
		return (true);
	}
	return (false);
}

int	remove_quotes_loop(char *new_line, char *line, int status)
{
	int		i;
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	remove_quotes_init(&i, &j, &in_single_quotes, &in_double_quotes);
	while (line[i])
	{
		if (quotes_check(line[i], &in_single_quotes, &in_double_quotes))
			(void)i;
		else if ((!in_single_quotes && !in_double_quotes) && line[i] == '\\')
			new_line[j++] = line[++i];
		else if (!in_single_quotes && line[i] == '$')
		{
			if (line[i + 1] == '?')
				replace_exit_status_var(new_line, status, &i, &j);
			else
				replace_env_var(new_line, line, &i, &j);
		}
		else if ((in_single_quotes && line[i] != '\'') || (!in_single_quotes
				&& !in_double_quotes) || (in_double_quotes && line[i] != '"'))
			new_line[j++] = line[i];
		i++;
	}
	return (j);
}

char	*remove_quotes(char *line, int status)
{
	int		j;
	char	*new_line;

	new_line = (char *)malloc(LINE_MAX * sizeof(char));
	if (new_line == NULL)
		fatal_error("malloc");
	j = remove_quotes_loop(new_line, line, status);
	new_line[j] = '\0';
	return (new_line);
}

void	expand(t_token *tokens, int status)
{
	t_token	*pt;
	char	*new_token;

	pt = tokens;
	while (pt)
	{
		if (ft_strchr(pt->token, '\'') != NULL
			|| ft_strchr(pt->token, '"') != NULL
			|| ft_strchr(pt->token, '\\') != NULL
			|| ft_strchr(pt->token, '$'))
		{
			new_token = remove_quotes(pt->token, status);
			free(pt->token);
			pt->token = new_token;
		}
		pt = pt->next;
	}
}
