#include <libc.h>

int interpret(char *line)
{
    char *argv[] = {line, NULL};
    pid_t pid = fork();

    if(pid == 0)
    {
        execve(line, argv, 0);
        exit(0);
    }
    else
    {
        wait(0);
    }
    return 0;
}


int main()
{
    interpret("/bin/ls");
    printf("This line should not be printed\n");
}
