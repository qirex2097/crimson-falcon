#include "minishell.h"

static int builtin_dummy(char **argv);
static int builtin_cd(char **argv);

// 下の２つにコマンド名と呼び出す関数を登録する
#define BUILTIN_LIST {"", "cd", "ttt", NULL, }
#define BUILTIN_FUNC {builtin_dummy, builtin_cd, builtin_dummy, NULL, }

int is_builtin(char **argv)
{
    char *command = argv[0];
    char *builtin_list[] = BUILTIN_LIST;
    int i;

    i = 1;
    while (builtin_list[i]) {
        if (strcmp(builtin_list[i], command) == 0) {
            return i;
        }
        i++;
    }
    
    return 0;
}

int exec_builtin_command(char **argv)
{
    int (*builtin_func[])(char **) = BUILTIN_FUNC;
    int builtin_no;
    int status;
    
    builtin_no = is_builtin(argv);
    status = builtin_func[builtin_no](argv);
    
    return(status);
}

int builtin_dummy(char **argv)
{
    printf("builtin_dummy:%s\n", argv[0]);
    return 0;
}

int builtin_cd(char **argv)
{
    if (argv[1] == NULL)
    {
        chdir(getenv("HOME"));
    }
    else
    {
        if (chdir(argv[1]) == -1)
        {
            perror("cd");
        }
    }
    return(0);
}
