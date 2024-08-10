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
    if(node == NULL)
        fatal_error("new_node:malloc error\n");
    node->kind = kind;
    node->next = NULL;
    node->args = malloc(sizeof(char*) * 100);
    if (!node->args) 
    {
        fatal_error("new_node:malloc error\n");
    }
    node->args[0] = NULL;
    node->redirects = NULL;
    return (node);
}

t_r_node *new_r_node(t_node_kind kind, char* filename)
{
    t_r_node *node = malloc(sizeof(t_r_node));
    if (node == NULL)
        fatal_error("new_r_node: malloc error");
    node->kind = kind;
    node->filename = strdup(filename);
    node->fd = -1;
    node->next = NULL;
    return (node);
}

void append_redirect_node(t_node *node, t_r_node *child_node)
{
    t_r_node *p;

    if (node->redirects == NULL)
    {
        node->redirects = child_node;
    } else {
        p = node->redirects;
        while (p->next)
            p = p->next;
        p->next = child_node;
    }
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

int append_command_element(t_node *node, char **tokens)
{
    t_r_node *redirect_node;
    
    if (strcmp(">", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_r_node(ND_REDIR_OUT, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else if (strcmp("<", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_r_node(ND_REDIR_IN, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else if (strcmp(">>", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_r_node(ND_REDIR_APPEND, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else if (strcmp("<<", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_r_node(ND_REDIR_HEREDOC, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else {
        append_tok(node, tokens[0]);
        return 1;
    }
}

t_node  *parse(char **tokens)
{
    int i;
    t_node  *node = new_node(ND_SIMPLE_CMD);
    i = 0;
    while (tokens[i])
    {
        i += append_command_element(node, &tokens[i]);
    }
    return (node);
}