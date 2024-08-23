#include "minishell.h"

static int builtin_dummy(char **argv);
static int builtin_cd(char **argv);
static int builtin_echo(char **argv);
static int builtin_env(char **argv);


// 下の２つにコマンド名と呼び出す関数を登録する
#define BUILTIN_LIST {"", "cd", "echo", "env", NULL, }
#define BUILTIN_FUNC {builtin_dummy, builtin_cd, builtin_echo, builtin_env, NULL, }

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


bool    check_n_option(const char *argv)
{
    size_t i;

    if(strncmp(argv, "-n", 2) != 0)
        return (false);
    
    i = 2;
    while(argv[i] != '\0')
    {
        if(argv[i]!= 'n')
            return (false);
        i++;
    }
    return true;
}

int builtin_echo(char **argv)
{
    size_t i = 1;
    bool    print_newline = true;

    while(argv[i] && check_n_option(argv[i]))
    {
        print_newline = false;
        i++;
    }

    while(argv[i])
    {
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if(argv[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if(print_newline == true)
        write(1, "\n", 1);
    return(0);
}

int builtin_env(char **argv)
{
    t_env *env;

    (void)argv;
    env = g_env_root;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
    return(0);
}