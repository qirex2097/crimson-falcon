/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:45:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/29 20:19:33 by kahori           ###   ########.fr       */
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

char *skip_token(char *line) 
{
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


void expand(char **args) 
{
    int i = 0;
    while (args[i] != NULL)
    {
        char *p = args[i];
        char   *buff;
        if(*p == '\'')
        {
            buff = ft_strtrim(p, "'");
        }
        else if (*p == '"')
            buff = ft_strtrim(p, "\"");
        else
        {
            buff = strdup(p);
        }
        free(args[i]);
        args[i] = buff;
        i++;
    }
}

char **tokenizer(char *line) {
    char *p;
    char *buff;
    char **buffs = malloc(sizeof(char *) * 1000);
    int i = 0;
    int len;

    if (buffs == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (*line) {
        line = skip_blank(line);
        if (*line == '\0')
            break;
        p = skip_token(line);
        len = p - line;
        buff = malloc(sizeof(char) * (len + 1));
        if (buff == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strncpy(buff, line, len);
        buff[len] = '\0';
       // printf("%s\n", buff);
        line = p;
        buffs[i] = buff;
        i++;
    }
    buffs[i] = NULL;
    i = 0;
    while(buffs[i])
    {
        printf("%s\n", buffs[i]);
        i++;
    }
    expand(buffs);

    return buffs;
}

/*TODO expand
' " を取り除くexpand
void    expand(char **args);
*/

/*TODO ¥
¥の後の空白は空白として扱う

ls MY¥ Documents
-> 
ls 
MY Documents
*/