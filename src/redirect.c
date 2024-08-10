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

int open_redir_file(t_r_node *redir, int *backup_fd) 
{
    int status = 0;

    if (redir == NULL) return 0;
    if (redir->kind == ND_REDIR_OUT) {
       redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (redir->fd < 0) {
            return -1;//ファイルオープンエラー
        }
        if (backup_fd[1] < 0) {
            backup_fd[1] = dup(STDOUT_FILENO);
            if (backup_fd[1] < 0) {
                return -1;
            }
        }
    } else if (redir->kind == ND_REDIR_IN) {
        redir->fd = open(redir->filename, O_RDONLY);
        if (redir->fd < 0) {
            perror("open_redir_file");
            return -1;//ファイルオープンエラー
        }
        if (backup_fd[0] < 0) {
            backup_fd[0] = dup(STDIN_FILENO);
            if (backup_fd[0] < 0) {
                return -1;
            }
        }
    } else if (redir->kind == ND_REDIR_APPEND) {
        redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (redir->fd < 0) {
            return -1;//ファイルオープンエラー
        }
        if (backup_fd[1] < 0) {
            backup_fd[1] = dup(STDOUT_FILENO);
            if (backup_fd[1] < 0) {
                return -1;
            }
        }
    } else if (redir->kind == ND_REDIR_HEREDOC) {
        redir->fd = create_heredoc(redir->filename);
        if (redir->fd < 0) {
            return -1;//
        }
        if (backup_fd[0] < 0) {
            backup_fd[0] = dup(STDIN_FILENO);
            if (backup_fd[0] < 0) {
                return -1;
            }
        }
    }
    status = open_redir_file(redir->next, backup_fd);
    if (status < 0 && redir->fd >= 0) {
        close(redir->fd);
        redir->fd = -1;
    }
    return (status);
}

int do_redirect(t_r_node *redir)
{
    if (redir == NULL) return 0;

    if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_APPEND) {
        if (dup2(redir->fd, STDOUT_FILENO) < 0) {
            return -1;
        }
    } else if (redir->kind == ND_REDIR_IN || redir->kind == ND_REDIR_HEREDOC) {
        if (dup2(redir->fd, STDIN_FILENO) < 0) {
            return -1;
        }
    }
    return do_redirect(redir->next);
}

void close_redirect_files(t_r_node *redir)
{
    if (redir == NULL) return;
    
    if (redir->fd >= 0)
    {
        close(redir->fd);
    }
    close_redirect_files(redir->next);
}

int reset_redirect(int *backup_fd)
{
    if (backup_fd[1] >= 0) {
        if (dup2(backup_fd[1], STDOUT_FILENO) < 0) {
            return -1;
        }
        close(backup_fd[1]);
    }
    if (backup_fd[0] >= 0) {
        if (dup2(backup_fd[0], STDIN_FILENO) < 0) {
            return -1;
        }
        close(backup_fd[0]);
    }
    return 0;
}
