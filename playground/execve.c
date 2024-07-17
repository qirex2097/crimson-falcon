#include <libc.h>

int main()
{
    char *args[3] = {"/bin/ls", NULL};
    execve("/bin/ls", args, 0);
    printf("execve failed\n");
}
