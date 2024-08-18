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

#define COMMAND_LINE_OPERATORS   {">>", "<<", ">", "<", ";", "|"," ", NULL}

bool is_command_line_operator(char *line)
{
    char *operators[] = COMMAND_LINE_OPERATORS;
    int i;
    
    i = 0;
    while (operators[i]) {
        if (strncmp(operators[i], line, strlen(operators[i])) == 0) 
            return (true);
        i++;
    }
    return (false);
}

char *skip_command_line_operator(char *line)
{
    char *operators[] = COMMAND_LINE_OPERATORS;
    int i;

    i = 0;
    while (operators[i]) {
        if (strncmp(operators[i], line, strlen(operators[i])) == 0) 
            return (line + strlen(operators[i]));
        i++;
    }

    return line;
}

char    *skip_blank(char *line)
{
    char    *current = line;
    while (*current == ' ' && *current)
        current++;
    return current;
}

char *skip_quate(char *p, char quote)
{
    if(*p != quote)
        return(p);
    p++;
    while(*p != quote && *p)
        p++;
    if(*p == quote)
        p++;
    else
    {
        xperror("unexpected EOF while looking for matching \'or\".");
        return(NULL);
    }
    return(p);
}

char *skip_token(char *line)
{
    char *p;

    p = line;
    if(*p == '\'' || *p == '"')
    {
        p = skip_quate(p, *p);
    }
    else
    {
        if (is_command_line_operator(p))
            return skip_command_line_operator(p);
        while(p && !is_command_line_operator(p) && *p)
        {
            if(*p == '\\') {
                if(*p == '\\' && *(p + 1) == '\0') {//バックスラッシュで終了した場合はエラー
                    xperror("unexpected EOF while looking for matching `\\'");
                    return(NULL);
                }
                p += 2;
            }
            else
            {
                if(*p == '\'' || *p == '"')
                    p = skip_quate(p, *p);
                else
                    p++;
            }
        }
    }
    return(p);
}

char    *copy_token(char *start, char *end)
{
    char    *token;
    char    *src;
    char    *dest;

    token = malloc(sizeof(char) * (end - start + 1));
    if(token == NULL)
    {
        fatal_error("copy_token");
    }

    src = start;
    dest = token;
    while(src < end)
    {
        if(*src == '\\' && *(src + 1) != '\0')
            src++;
        *dest++ = *src++;
    }
    *dest = '\0';
    return(token);
}

t_token *append_token(char *start, char *end)
{
    t_token *p;
    
    p = (t_token *)malloc(sizeof(t_token));
    if (p == NULL) 
    {
        fatal_error("malloc");
        return(NULL);
    }
    p->token = copy_token(start, end); //トークンの文字列をコピーする
    if (is_command_line_operator(p->token))
    {
        if (strncmp(p->token, ";", 1) == 0)
            p->kind = TOKEN_DELIMITER;
        else
            p->kind = TOKEN_OPERATOR;
    }
    else
        p->kind = TOKEN_WORD;
    p->next = NULL;
    return(p);
}

void free_tokens(t_token *tokens)
{
    if (tokens->next == NULL)
    {
        free(tokens->token);
        free(tokens);
    }
    else
    {
        free_tokens(tokens->next);
    }
}

t_token *tokenizer(char *line)
{
    char    *start;
    char    *curr;
    t_token head;
    t_token *p;

    head.next = NULL;
    p = &head;
    curr = line;
    while (*curr)
    {
        curr = skip_blank(curr);
        if (*curr == '\0')
            break;

        start = curr;
        curr = skip_token(curr);
        if (curr == NULL)//',"を閉じていない場合
        {
            free_tokens(head.next);
            return(NULL);
        }
        p->next = append_token(start, curr); //tokenをcopyして格納する
        p = p->next;
    }

    return(head.next);
}

bool is_word(t_token *token)
{
    return(token && token->kind == TOKEN_WORD);
}

bool is_operator(t_token *token)
{
    return(token && token->kind == TOKEN_OPERATOR);
}

bool is_delimiter(t_token *token)
{
    return(token && token->kind == TOKEN_DELIMITER);
}

bool is_pipe(t_token *token)
{
    return(token && token->kind == TOKEN_OPERATOR && strncmp(token->token, "|", 1) == 0);
}