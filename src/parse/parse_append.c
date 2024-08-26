/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:16:43 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:52:00 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

// args[]の大きさはTOKEN_MAX
t_token	*append_args_element(t_cmd *node, t_token *token)
{
	int	i;

	i = 0;
	while (node->args[i] && i < TOKEN_MAX - 1)
		i++;
	node->args[i] = ft_strdup(token->token);
	node->args[i + 1] = NULL;
	return (token->next);
}
