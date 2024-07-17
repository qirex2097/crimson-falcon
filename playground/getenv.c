#include <libc.h>

 char *serch_path(const char *filename)
{
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        char *path_token = strtok(path_copy, ":");
        char *full_path = malloc(strlen(path_token) + strlen(filename) + 2);
        while(path_token)
        {
            strcpy(full_path, path_token);
            strcat(full_path, "/");
            strcat(full_path, filename);
            if(access(full_path, F_OK) == 0)
            {
                free(path_copy);
                return full_path;
            }
            path_token = strtok(NULL, ":");
        }
        free(path_copy);
        return NULL;
    
}

int main()
{
    char *path = serch_path("pwd");
    printf("%s\n", path);
    free(path);
    return 0;
}
