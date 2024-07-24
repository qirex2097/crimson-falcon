/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:45:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/24 21:27:15 by kahori           ###   ########.fr       */
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

char *skip_token(char *line) {
    char *p = line;

    //single quote
    if (*p == '\'') {
        p++;
        while (*p != '\'' && *p)
            p++;
        if (*p == '\'')
            p++;
    }
    //double quote
    else if (*p == '"')
    {
        p++;
        while (*p != '"' && *p)
            p++;
        if (*p == '"')
            p++;
    }
    else
    {
        while (*p != ' ' && *p)
            p++;
    }
    return p;
}


char    **tokenizer(char *line)
{
    char *p;
    char *buff;
    char *buffs[1000];
    int i;
    int len;

    i = 0;
    while(*line)
    {
        line = skip_blank(line);
        if(*line == '\0')
            break;
        p = skip_token(line);
        len = p - line;
        buff = malloc(sizeof(char)* (len + 1));
        strncpy(buff, line, len);
//        printf("buff:%s\n", buff);
		buff[len] = '\0';
        line = p;
        buffs[i] = buff;
        i++;
    }
    buffs[i] = NULL;
    char **argv;
    i = 0;
    argv = malloc(sizeof(char *) * (i + 1));
    while (buffs[i]) {
        argv[i] = buffs[i];
        i++;
    }
    argv[i] = NULL;
    return argv;
}