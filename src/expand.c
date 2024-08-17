#include "minishell.h"

void expand(t_token *tokens)
{
    t_token *q;

    q = tokens;
    while (q)
    {
        char *p = q->token;
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
        free(q->token);
        q->token = buff;
        q = q->next;
    }
}

