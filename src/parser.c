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

t_node  *new_node(t_node_kind kind)
{
    t_node  *node = malloc(sizeof(t_node));
    if(!node)
    {
        fatal_error("new_node:malloc error\n");
    }
    node->kind = kind;
    node->next = NULL;
    node->args = malloc(sizeof(char*) * 100);
    if (!node->args) 
    {
        fatal_error("new_node:malloc error\n");
    }
    node->args[0] = NULL;
    return (node);
}

void append_tok(t_node *node, char *token)
{
    int i;
    i = 0;
    while (node->args[i]) 
        i++;
    node->args[i] = strdup(token);
    node->args[i + 1] = NULL;
    // node->args のインデックスのチェック
    
    return;
}

t_node  *parse(char **tokens)
{
    int i;
    t_node  *node = new_node(ND_SIMPLE_CMD);
    i = 0;
    while (tokens[i])
    {
        append_tok(node, tokens[i]);
        i++;
    }
    return (node);
}