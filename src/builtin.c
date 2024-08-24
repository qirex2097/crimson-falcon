#include "minishell.h"

static int builtin_dummy(char **argv);
static int builtin_cd(char **argv);
static int builtin_echo(char **argv);
static int builtin_env(char **argv);
static int builtin_pwd(char **argv);
static int builtin_export(char **argv);
static int builtin_unset(char **argv);
static int builtin_exit(char **argv);


// 下の２つにコマンド名と呼び出す関数を登録する
#define BUILTIN_LIST { "", "cd", "echo", "env", "pwd", "export", "unset", "exit", NULL, }
#define BUILTIN_FUNC { builtin_dummy, builtin_cd, builtin_echo, builtin_env, builtin_pwd, builtin_export, builtin_unset, builtin_exit, NULL, }

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
    char buff[PATH_MAX];
    
    if (getcwd(buff, PATH_MAX) == 0)
    {
        perror("minishell: cd");
    }
    else
    {
        ms_setenv("OLDPWD", buff, 1);
    }
    if (argv[1] == NULL)
    {
        if (ms_getenv("HOME") == NULL)
        {
            ms_perror("cd: HOME not set");
            return 1 * 256;
        }
        if (chdir(ms_getenv("HOME")) == -1)
        {
            perror("minishell: cd");
        }
    }
    else
    {
        if (chdir(argv[1]) == -1)
        {
            perror("minishell: cd");
        }
   }
    if (getcwd(buff, PATH_MAX) == 0)
    {
        perror("minishell: cd");
    }
    ms_setenv("PWD", buff, 1);
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
    env = g_env_root.next;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
    return(0);
}

int builtin_pwd(char **argv)
{
    char buff[PATH_MAX];
    (void)argv;
    
    if (getcwd(buff, PATH_MAX) == NULL)
    {
        perror("minishell: pwd");
        return(-1);
    }
    printf("%s\n", buff);
    return(0);
}

int builtin_export(char **argv)
{
    char *equals;
    char key[1024];
    char value[1024];
    int i;

    (void)argv;
    if (argv[1] == NULL)
    {
        return builtin_env(NULL);
    }
    else
    {
        i = 1;
        while (argv[i])
        {
            equals = strchr(argv[i], '=');
            if (equals != NULL)
            {
                strncpy(key, argv[i], equals - argv[i]);
                key[equals - argv[i]] = '\0';
                strncpy(value, equals + 1, strlen(equals + 1) + 1);
                if (!is_valid_env_name(key))
                {
                    return(1);
                }
                ms_setenv(key, value, 1);
            }
            i++;
        }
    }

    return(0);
}

int builtin_unset(char **argv)
{
    char *equals;
    int i;
    
    (void)argv;
    if (argv[1] == NULL)
    {
        return(0);
    }
    else
    {
        i = 1;
        while (argv[i])
        {
            equals = strchr(argv[i], '=');
            if (equals) //'='を含む
            {
                ms_perror("unset: `=': not a valid identifier");
                return(-1);
            }
            ms_unsetenv(argv[i]);
            i++;
        }
    }

    return(0);
}

int builtin_exit(char **argv)
{
    int value;
    value = 0;
    if (argv[1])
    {
        value = atoi(argv[1]);
    }
    exit(value);
    return (0);
}