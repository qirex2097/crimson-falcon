#include "minishell.h"

void heredoc_loop(const char *delimiter, int fd)
{
    char *line;
    while (1)
    {
        readline_interrupted = false;
        line = readline("> ");
        if (line == NULL)
            break;
        if (readline_interrupted || strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        if (fd >= 0)
        {
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
        }
        free(line);
    }
    rl_on_new_line();
//    rl_replace_line("", 0);
//    rl_redisplay();
    return;
}

int create_heredoc(const char* delimiter)
{
    int pfd[2];
    
    if (pipe(pfd) < 0)
        fatal_error("pipe");
    readline_interrupted = false;
    heredoc_loop(delimiter, pfd[1]);
    close(pfd[1]);
    if (readline_interrupted)
    {
        close(pfd[0]);
        return -1;
    }
    return (pfd[0]);
}

int open_heredoc(t_redirect *redir)
{
    while (redir->next)
    {
        readline_interrupted = false;
        heredoc_loop(redir->filename, -1);
        redir = redir->next;
    }
    return create_heredoc(redir->filename);
}

int open_redir_file_sub(t_redirect *redir)
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
        redir->fd = open_heredoc(redir);
        target_fd = STDIN_FILENO;
    } else {
        return -1;//Unknown redirection type
    }
    
    if (redir->fd < 0)
    {
        perror(redir->filename);
        return -1;//File Open Error
    }
    
    if (dup2(redir->fd, target_fd) < 0)
    {
        perror("dup2");
        close(redir->fd);
        return -1;//Dup2 Error
    }
    close(redir->fd);

    if (redir->kind == ND_REDIR_HEREDOC)
        return status;
    status = open_redir_file_sub(redir->next);
    return (status);
}

int open_redir_file(t_redirect *redir, t_redirect *heredoc)
{
    int status = 0;

    if (heredoc != NULL)
    {
        status = open_redir_file_sub(heredoc);
        if (status != 0)
            return status;
    }
    return open_redir_file_sub(redir);
}

