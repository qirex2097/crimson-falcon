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

void    expand(char **args)
{
    int i = 0;
    char *p = *args[i];
    char *buff;
    buff = malloc(strlen(p) + 1);
    //error
    if
}

void tokenizer(char *line)
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
    i = 0;
    while (buffs[i]) {
        printf("%s\n", buffs[i]);
        i++;
    }
}



int main()
{
    char *line = "ls       -l | cat -e 'hello       world' \"hello     world\"";
    // printf("$%s$\n", skip_blank(line));
    tokenizer(line);
    return(0);
}
