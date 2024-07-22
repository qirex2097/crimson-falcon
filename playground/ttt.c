#include <stdio.h>
#include <libc.h>

char    *skip_blank(char *line)
{
    char    *current = line;
    while (*current == ' ' && *current)
        current++;
    return current;
}

char    *skip_word(char *line)
{
    char    *p = line;

    while(*p != ' ' && *p)
        p++;
    return  p;
}

void tokenizer(char *line)
{
    char *p;
    char *buff;
    char *buffs[1000];
    int i;

    i = 0;
    while(*line)
    {
        line = skip_blank(line);
        if(*line == '\0')
            break;
        p = skip_word(line);
        buff = malloc(sizeof(char)* (p - line + 1));
        strncpy(buff, line, p-line);
//        printf("buff:%s\n", buff);
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
    char *line = "    ls    -l | cat -e";
    // printf("$%s$\n", skip_blank(line));
    tokenizer(line);
}