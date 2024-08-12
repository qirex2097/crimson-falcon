#include "minishell.h"

int create_heredoc(const char* delimiter)
{
    char *line;
    int pfd[2];
    
    if (pipe(pfd) < 0)
        fatal_error("pipe");
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pfd[1], line, strlen(line));
        write(pfd[1], "\n", 1);
        free(line);
    }
    close(pfd[1]);
    return (pfd[0]);
}

int open_redir_file(t_redirect *redir)
{
    int status = 0;
    int target_fd;

    if (redir == NULL) return 0;

    if (redir->kind == ND_REDIR_OUT) {
        redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        target_fd = STDOUT_FILENO;
    } else if (redir->kind == ND_REDIR_IN) {
        redir->fd = open(redir->filename, O_RDONLY);
        target_fd = STDIN_FILENO;
    } else if (redir->kind == ND_REDIR_APPEND) {
        redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
        target_fd = STDOUT_FILENO;
    } else if (redir->kind == ND_REDIR_HEREDOC) {
        redir->fd = create_heredoc(redir->filename);
        target_fd = STDIN_FILENO;
    } else {
        return -1;//Unknown redirection type
    }
    
    if (redir->fd < 0)
    {
        perror("open");
        return -1;//File Open Error
    }
    
    if (dup2(redir->fd, target_fd) < 0)
    {
        perror("dup2");
        close(redir->fd);
        return -1;//Dup2 Error
    }
    close(redir->fd);

    status = open_redir_file(redir->next);
    return (status);
}
