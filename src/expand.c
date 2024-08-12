#include "minishell.h"

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

