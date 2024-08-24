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

void initialize_cmd(t_cmd *cmd)
{
    cmd->args = malloc(sizeof(char*) * TOKEN_MAX);
    if (cmd->args == NULL) 
        fatal_error("malloc error");
    cmd->args[0] = NULL;
    cmd->redirects = NULL;
    cmd->next = NULL;
    return;
}

t_cmd *new_cmd()
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (cmd == NULL)
        fatal_error("malloc error");
    initialize_cmd(cmd);
    return cmd;
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
    node->filename = ft_strdup(filename);
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
void append_heredoc_node(t_cmd *node, t_redirect *child_node)
{
    t_redirect *p;

    if (node->heredoc == NULL)
    {
        node->heredoc = child_node;
    } else {
        p = node->heredoc;
        while (p->next)
            p = p->next;
        p->next = child_node;
    }
}
t_token *append_redirect_element(t_cmd *node, t_token *tokens)
{
    t_redirect *redirect_node;
    
    if (ft_strcmp(">", tokens->token) == 0 && is_word(tokens->next)) {
        redirect_node = new_redirect(ND_REDIR_OUT, tokens->next->token);
        append_redirect_node(node, redirect_node);
        return tokens->next->next;
    } else if (ft_strcmp("<", tokens->token) == 0 && is_word(tokens->next)) {
        redirect_node = new_redirect(ND_REDIR_IN, tokens->next->token);
        append_redirect_node(node, redirect_node);
        return tokens->next->next;
    } else if (ft_strcmp(">>", tokens->token) == 0 && is_word(tokens->next)) {
        redirect_node = new_redirect(ND_REDIR_APPEND, tokens->next->token);
        append_redirect_node(node, redirect_node);
        return tokens->next->next;
    } else if (ft_strcmp("<<", tokens->token) == 0 && is_word(tokens->next)) {
        redirect_node = new_redirect(ND_REDIR_HEREDOC, tokens->next->token);
        // append_redirect_node(node, redirect_node);
        append_heredoc_node(node, redirect_node);
        return tokens->next->next;
    }
    
    perror("parse error");
    return NULL;
}

t_token* append_args_element(t_cmd *node, t_token *token)
{
    int i;
    i = 0;
    while (node->args[i] && i < TOKEN_MAX - 1) // node->args のインデックスのチェック
        i++;
    node->args[i] = ft_strdup(token->token);
    node->args[i + 1] = NULL;
    
    return(token->next);
}

t_node *parse_cmd(t_token *tokens)
{
    t_token *pt;
    t_node *node;
    t_cmd *cmd;
    
    pt = tokens;
    if (is_pipe(pt))
    {
        ms_perror("syntax error near unexpected token `|'");
        return NULL;
    }
    
    node = new_node(ND_SIMPLE_CMD);
    cmd = &node->command;
    while(pt && !is_delimiter(pt))
    {
        if (is_pipe(pt)) {
            if (pt->next == NULL || !is_word(pt->next))
            {
                perror("parse error");
                free_node(node);
                return NULL;
            }
            cmd->next = new_cmd();
            cmd = cmd->next;
            pt = pt->next;
        } else if (is_word(pt)) {
            pt = append_args_element(cmd, pt);
        } else {
            pt = append_redirect_element(cmd, pt);
        }
    }
    
    return node;
}

t_token *skip_delimiter(t_token *tokens)
{
    t_token *pt = tokens;
    while (is_delimiter(pt))
        pt = pt->next;
    return(pt);
}

void split_command_line(t_token *tokens, t_token **table, int table_max)
{
    int i;
    t_token *pt;
    
    pt = skip_delimiter(tokens);
    i = 0;
    table[i] = pt;
    i++;
    while(pt && i < table_max - 1)
    {
        while(pt && !is_delimiter(pt))
        {
            pt = pt->next;
        }
        pt = skip_delimiter(pt);
        table[i] = pt;
        i++;
    }
    table[i] = NULL;
    return;
}

t_node *parse(t_token *tokens)
{
    t_node head;
    t_node *p;
    t_token *pt_table[100];
    int i;

    split_command_line(tokens, pt_table, 100);

    head.next = NULL;
    p = &head;
    i = 0;
    while(pt_table[i])
    {
        p->next = parse_cmd(pt_table[i]);
        if (p->next == NULL)
        {
            free_node(head.next);
            return NULL;
        }
        p = p->next;
        i++;
    }

    return head.next;
}