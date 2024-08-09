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
    t_node  *next;
    t_node  *node = calloc(1, sizeof(t_node));
    if(!node)
    {
        printf("calloc error\n");
        exit(1);
    }
    node->kind = kind;
    node->next = next;
    return(node);
}

t_node  *parse(char **tokens)
{
    t_node  *node = new_node(ND_SIMPLE_CMD);
}