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

char	*skip_token_loop(char *p)
{
	while (p && !is_command_line_operator(p) && *p)
	{
		if (*p == '\\')
		{
			if (*p == '\\' && *(p + 1) == '\0')
			{
				ms_perror("unexpected EOF while looking for matching `\\'");
				return (NULL);
			}
			p += 2;
		}
		else
		{
			if (*p == '\'' || *p == '"')
				p = skip_quate(p, *p);
			else
				p++;
		}
	}
	return (p);
}

char	*skip_token(char *line)
{
	char	*p;

	p = line;
	if (*p == '\'' || *p == '"')
		p = skip_quate(p, *p);
	else
	{
		if (is_command_line_operator(p))
			return (skip_command_line_operator(p));
		return (skip_token_loop(p));
	}
	return (p);
}

char	*copy_token(char *start, char *end)
{
	char	*token;
	char	*src;
	char	*dest;

	token = malloc(sizeof(char) * (end - start + 1));
	if (token == NULL)
	{
		fatal_error("copy_token");
	}
	src = start;
	dest = token;
	while (src < end)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (token);
}

t_token	*append_token(char *start, char *end)
{
	t_token	*p;

	p = (t_token *)malloc(sizeof(t_token));
	if (p == NULL)
	{
		fatal_error("malloc");
		return (NULL);
	}
	p->token = copy_token(start, end);
	if (is_command_line_operator(p->token))
	{
		if (ft_strncmp(p->token, ";", 1) == 0)
			p->kind = TOKEN_DELIMITER;
		else
			p->kind = TOKEN_OPERATOR;
	}
	else
		p->kind = TOKEN_WORD;
	p->next = NULL;
	return (p);
}

void	free_tokens(t_token *tokens)
{
	if (tokens == NULL)
		return;
	free_tokens(tokens->next);
	free(tokens->token);
	free(tokens);
}
