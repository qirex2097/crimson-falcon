#include "minishell.h"

void open_redir_file(t_r_node *redir) 
{
    if (redir == NULL) return;
    if (redir->kind == ND_REDIR_OUT)
        printf("%s(%d): >%s\n", __FILE__, __LINE__, redir->filename);
    if (redir->kind == ND_REDIR_IN)
        printf("%s(%d): <%s\n", __FILE__, __LINE__, redir->filename);
    if (redir->kind == ND_REDIR_APPEND)
        printf("%s(%d): >>%s\n", __FILE__, __LINE__, redir->filename);
    open_redir_file(redir->next);
}

void do_redirect(t_r_node *redir)
{
    if (redir == NULL) return;
    printf("%s(%d): %s\n", __FILE__, __LINE__, redir->filename);
    do_redirect(redir->next);
}

void reset_redirect(t_r_node *redir)
{
    if (redir == NULL) return;
    reset_redirect(redir->next);
    printf("%s(%d): %s\n", __FILE__, __LINE__, redir->filename);
}
