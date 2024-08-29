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

#define TOKEN_MAX 200

/* parse_new.c */
void		initialize_cmd(t_cmd *cmd);
t_cmd		*new_cmd(void);
t_node		*new_node(t_node_kind kind);
t_redirect	*new_redirect(t_node_kind kind, char *filename);

/* parse_append.c */
void		append_redirect_node(t_cmd *node, t_redirect *child_node);
t_token		*append_redirect_element(t_cmd *node, t_token *tokens);
t_token		*append_args_element(t_cmd *node, t_token *token);

/* parse_redirect.c */
bool		is_redirect(t_token *pt);

/* parse_utils.c */
void		split_by_delimiter(t_token *tokens, t_token **table, int table_max);
