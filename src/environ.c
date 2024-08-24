#include "minishell.h"

char *ft_strndup(const char *str, int n)
{
    char *line;
    int i;

    line = malloc(sizeof(char) * (n + 1));
    i = 0;
    while (i < n)
    {
        line[i] = str[i];
        i++;
    }
    line[i] = '\0';
    return(line);
}

t_env *new_env_var(const char *key, const char *value)
{
    t_env *new_var = malloc(sizeof(t_env));
    new_var->key = strdup(key);
    new_var->value = strdup(value);
    new_var->next = NULL;
    return(new_var);
}

void free_env_var(t_env *env)
{
    free(env->key);
    free(env->value);
    free(env);
    return;
}

t_env *initialize_env()
{
    t_env head;
    t_env *new_env;
    extern char **environ;
    int i;
    char *equals;
    char key[1024];
    char value[1024];

    i = 0;
    head.next = NULL;
    while (environ[i])
    {
        equals = strchr(environ[i], '=');
        if (equals)
        {
            strncpy(key, environ[i], equals - environ[i]);
            key[equals - environ[i]] = '\0';
            strncpy(value, equals + 1, strlen(equals + 1) + 1);
            new_env = new_env_var(key, value);
            new_env->next = head.next;
            head.next = new_env;
        }
        i++;
    }
    return(head.next);
}

void cleanup_env(t_env *env_root)
{
    t_env *current;

    current = env_root;
    while (current)
    {
        t_env *next = current->next;
        free_env_var(current);
        current = next;
    }
}

char **create_env_array(t_env *env_root)
{
    int count, i;
    t_env *current;
    char **env_array;

    count = 0;
    current = env_root;
    while(current)
    {
        count++;
        current = current->next;
    }
    
    env_array = malloc(sizeof(char *) * (count + 1));
    if (env_array == NULL)
        fatal_error("malloc");
    i = 0;
    current = env_root;
    while (current)
    {
        env_array[i] = malloc(strlen(current->key) + strlen(current->value) + 2);
        sprintf(env_array[i], "%s=%s", current->key, current->value);
        i++;
        current = current->next;
    }
    env_array[i] = NULL;
    
    return env_array;
}

const char *ms_getenv(const char *key)
{
    t_env *env;
    
    env = g_env_root.next;
    while(env)
    {
        if (strcmp(key, env->key) == 0)
            return(env->value);
        env = env->next;
    }
    return(NULL);
}

int ms_setenv(const char *key, const char *value, int overwrite)
{
    t_env *env;
    t_env *new_env;

    env = g_env_root.next;
    while(env)
    {
        if (strcmp(env->key, key) == 0)
        {
            if (overwrite != 0)
            {
                free(env->value);
                env->value = strdup(value);
            }
            return(0);
        }
        env = env->next;
    }
    new_env = new_env_var(key, value);
    if (new_env == NULL)
    {
        fatal_error("malloc");
        return(-1);
    }
    new_env->next = g_env_root.next;
    g_env_root.next = new_env;
    return(0);
}

int ms_unsetenv(const char *key)
{
    t_env *prev_env;
    t_env *env;

    prev_env = &g_env_root;
    env = g_env_root.next;
    while(env)
    {
        if (strcmp(env->key, key) == 0)
        {
            prev_env->next = env->next;
            free(env);
            return(0);
        }
        prev_env = env;
        env = env->next;
    }
    return(0);
}