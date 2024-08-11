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

void initialize_cmd(t_cmd *cmd)
{
    cmd->args = malloc(sizeof(char*) * TOKEN_MAX);
    if (cmd->args == NULL) 
        fatal_error("malloc error");
    cmd->args[0] = NULL;
    cmd->redirects = NULL;
    return;
}

t_node *new_node(t_node_kind kind)
{
    t_node *node = malloc(sizeof(t_node));
    if (node == NULL)
        fatal_error("malloc error");
    node->kind = kind;
    node->next = NULL;
    initialize_cmd(&node->command);
    return (node);
}

t_redirect *new_redirect(t_node_kind kind, char* filename)
{
    t_redirect *node = malloc(sizeof(t_redirect));
    if (node == NULL)
        fatal_error("malloc error");
    node->kind = kind;
    node->filename = strdup(filename);
    node->fd = -1;
    node->next = NULL;
    return (node);
}

void append_redirect_node(t_cmd *node, t_redirect *child_node)
{
    t_redirect *p;

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

void append_tok(t_cmd *node, char *token)
{
    int i;
    i = 0;
    while (node->args[i] && i < TOKEN_MAX - 1) // node->args のインデックスのチェック
        i++;
    node->args[i] = strdup(token);
    node->args[i + 1] = NULL;
    
    return;
}

int append_command_element(t_cmd *node, char **tokens)
{
    t_redirect *redirect_node;
    
    if (strcmp(">", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_redirect(ND_REDIR_OUT, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else if (strcmp("<", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_redirect(ND_REDIR_IN, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else if (strcmp(">>", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_redirect(ND_REDIR_APPEND, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else if (strcmp("<<", tokens[0]) == 0) {
        // tokens[1]がファイル名として有効か調べる。ダメならエラー
        redirect_node = new_redirect(ND_REDIR_HEREDOC, tokens[1]);
        append_redirect_node(node, redirect_node);
        return 2;// トークンを２つ(tokens[0],[1])使用した
    } else {
        append_tok(node, tokens[0]);
        return 1;
    }
}

t_node *parse_cmd(char **tokens)
{
    int i;
    t_node  *node = new_node(ND_SIMPLE_CMD);
    i = 0;
    while (tokens[i] && strncmp(tokens[i], ";", 1) != 0)
    {
        i += append_command_element(&node->command, &tokens[i]);
    }
    return (node);
}

int skip_delimiter(char **tokens)
{
    int i = 0;
    while (strncmp(";", tokens[i], 1) == 0) i++;// デリミタを飛ばす
    
    return i;
}

t_node  *parse(char **tokens)
{
    t_node head;
    t_node *p;
    int table[100];
    int i, j, k;
    
    i = 0;
    j = skip_delimiter(&tokens[0]); // 先頭のデリミタを飛ばす
    table[i++] = j;
    while (tokens[j]) {
        k = skip_delimiter(&tokens[j]);
        if (k > 0)
            table[i++] = j + k;
        j = j + k + 1;
    }
    table[i] = -1;
    
    i = 0;
    p = &head;
    while (table[i] >= 0)
    {
        p->next = parse_cmd(&tokens[table[i]]);
        p = p->next;
        i++;
    }
    
    return head.next;
}    