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

t_env *initialize_env()
{
    t_env head;
    t_env *new_env;
    extern char **environ;
    int i;
    char *equals;
    char *key;
    char *value;

    i = 0;
    head.next = NULL;
    while (environ[i])
    {
        equals = strchr(environ[i], '=');
        if (equals)
        {
            key = ft_strndup(environ[i], equals - environ[i]);
            value = ft_strndup(equals + 1, strlen(equals + 1));
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
        free(current->key);
        free(current->value);
        free(current);
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
    
    env = g_env_root;
    while(env)
    {
        if (strcmp(key, env->key) == 0)
            return(env->value);
        env = env->next;
    }
    return(NULL);
}