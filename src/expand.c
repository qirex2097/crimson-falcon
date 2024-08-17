#include "minishell.h"

void remove_quotes(char *line)
{
    int i, j;
    bool in_single_quotes;
    bool in_double_quotes;

    i = j = 0;
    in_single_quotes = false;
    in_double_quotes = false;
    while(line[i])
    {
        if (line[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
        }
        else if (line[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
        }
        else if ((!in_single_quotes && !in_double_quotes) ||
                 (in_single_quotes && line[i] != '\'') ||
                 (in_double_quotes && line[i] != '"'))
        {
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}

void expand(t_token *tokens)
{
    t_token *pt;

    pt = tokens;
    while (pt)
    {
        remove_quotes(pt->token);
        pt = pt->next;
    }
}

