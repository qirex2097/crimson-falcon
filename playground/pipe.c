#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_cmd t_cmd;
struct s_cmd {
    t_cmd *next_cmd;
    char *command;
    char **args;
    int pfd[2];
};

void exec_cmd(t_cmd *cmd, int *prev_fd)
{
    t_cmd* curr_cmd = cmd;
    
    if (curr_cmd->next_cmd != NULL) {
        if (pipe(curr_cmd->pfd) == -1) {
            perror("pipe");
            exit(-1);
        }
    }
        
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(-1);
    } else if (pid == 0) {
        if (*prev_fd != -1) {
            dup2(*prev_fd, STDIN_FILENO);
            close(*prev_fd);
        }
        
        if (curr_cmd->next_cmd != NULL) {
            close(curr_cmd->pfd[0]);
            dup2(curr_cmd->pfd[1], STDOUT_FILENO);
            close(curr_cmd->pfd[1]);
        }
        
        execvp(curr_cmd->command, curr_cmd->args);
        perror("execvp");
        exit(-1);
    } else {
        if (*prev_fd != -1) {
            close(*prev_fd);
        }
        
        if (curr_cmd->next_cmd != NULL) {
            close(curr_cmd->pfd[1]);
            *prev_fd = curr_cmd->pfd[0];
        }
        
        wait(NULL);
    }
}

int main(int argc, char **argv)
{
    t_cmd *cmd;
    t_cmd cmd1 = { NULL, "ls", (char *[]){"ls", NULL}, {-1, -1}};
    t_cmd cmd2 = { NULL, "head", (char *[]){"head", NULL}, {-1, -1}};
    t_cmd cmd3 = { NULL, "wc", (char *[]){"wc", NULL}, {-1, -1}};
    cmd1.next_cmd = &cmd2;
    cmd2.next_cmd = &cmd3;
    cmd = &cmd1;
    int prev_fd;

    prev_fd = -1;
    while (cmd) {
        exec_cmd(cmd, &prev_fd);
        cmd = cmd->next_cmd;
    }

    return 0;
}