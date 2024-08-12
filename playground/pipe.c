#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t pid;
    int pfd[2];
    
    if (pipe(pfd) < 0)
        return -1;
    pid = fork();
    if (pid < 0)
        return -1;
    if (pid == 0) {
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        
        execlp("ls", "ls", NULL);
    } else {
        close(pfd[1]);
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        
        wait(NULL);
        
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}