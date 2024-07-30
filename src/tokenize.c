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

#include <stdio.h>
#include <libc.h>

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
        while(*p != ' ' && *p)
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

void expand(char **buffs) 
{
    int i = 0;
    while (buffs[i] != NULL)
    {
        char *p = buffs[i];
        char *buff;
        if(*p == '\'')
        {
            buff = ft_strtrim(p, "'");
        }
        else if (*p == '"')
        {
            buff = ft_strtrim(p, "\"");
        }
        else
        {
            buff = strdup(p);
        }
        free(buffs[i]);
        buffs[i] = buff;
        i++;
    }
}

char    *copy_token(char *start, char *end)
{
    char    *token;
    char    *src;
    char    *dest;

    token = malloc(sizeof(char) * (end - start + 1));
    if(token == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
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
        perror("malloc");
        exit(EXIT_FAILURE);
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
