#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *value;
    value = getenv("PATH");
    printf("%s=%s\n", "PATH", value);
    return 0;
}