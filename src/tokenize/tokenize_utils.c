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

bool	is_word(t_token *token)
{
	return (token && token->kind == TOKEN_WORD);
}

bool	is_operator(t_token *token)
{
	return (token && token->kind == TOKEN_OPERATOR);
}

bool	is_delimiter(t_token *token)
{
	return (token && token->kind == TOKEN_DELIMITER);
}

bool	is_pipe(t_token *token)
{
	return (token && token->kind == TOKEN_OPERATOR && ft_strncmp(token->token,
			"|", 1) == 0);
}
