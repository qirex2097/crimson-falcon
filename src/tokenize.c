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

static char *skip_quate(char *p, char quote)
{
    if(*p != quote)
        return(p);
    p++;
    while(*p != quote && *p)
        p++;
    if(*p == quote)
        p++;
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
        while(!is_command_line_operator(p) && *p)
        {
            if(*p == '\\' && *(p + 1) != '\0')
                p = p + 2;
            else if(*p == '\'' || *p == '"')
                p = skip_quate(p, *p);
            else
                p++;
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

char **tokenizer(char *line)
{
    int i;
    char    *start;
    char    **tokens;
    tokens = malloc(sizeof(char *) * 1000);
    if (tokens == NULL)
    {
        fatal_error("tokenizer");
    }

    i = 0;
    while (*line)
    {
        line = skip_blank(line);
        if (*line == '\0')
            break;

        start = line;
        line = skip_token(line);
        //tokenをcopyして配列に格納する
        tokens[i++] = copy_token(start, line);
    }
    tokens[i] = NULL;

    return tokens;
}
