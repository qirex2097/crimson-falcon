#include "minishell.h"

char	*ft_strndup(const char *str, int n)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ('0' <= c && c <= '9'))
		return (1);
	else
		return (0);
}

t_env	*new_env_var(const char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	return (new_var);
}

void	free_env_var(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
	return ;
}

t_env	*initialize_env_loop(char *start, char *end)
{
	char	key[1024];
	char	value[1024];

	ft_strncpy(key, start, end - start);
	key[end - start] = '\0';
	ft_strncpy(value, end + 1, ft_strlen(end + 1) + 1);
	return (new_env_var(key, value));
}

t_env	*initialize_env(void)
{
	t_env		head;
	t_env		*new_env;
	extern char	**environ;
	int			i;
	char		*equals;

	i = 0;
	head.next = NULL;
	while (environ[i])
	{
		equals = ft_strchr(environ[i], '=');
		if (equals)
		{
			new_env = initialize_env_loop(environ[i], equals);
			new_env->next = head.next;
			head.next = new_env;
		}
		i++;
	}
	return (head.next);
}

void	cleanup_env(t_env *env_root)
{
	t_env	*current;
	t_env	*next;

	current = env_root;
	while (current)
	{
		next = current->next;
		free_env_var(current);
		current = next;
	}
}

char	**malloc_env_array(t_env *env_root)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env_root;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (malloc(sizeof(char *) * (count + 1)));
}

char	**create_env_array(t_env *env_root)
{
	t_env	*current;
	char	**env_array;
	int		i;

	env_array = malloc_env_array(env_root);
	if (env_array == NULL)
		fatal_error("malloc");
	i = 0;
	current = env_root;
	while (current)
	{
		env_array[i] = malloc(ft_strlen(current->key)
				+ ft_strlen(current->value) + 2);
		sprintf(env_array[i], "%s=%s", current->key, current->value);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

bool	is_valid_env_name(const char *key)
{
	if (!key || !(*key) || (!ft_isalpha(*key) && *key != '_'))
		return (false);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (false);
		key++;
	}
	return (true);
}

const char	*ms_getenv(const char *key)
{
	t_env	*env;

	env = g_env_root.next;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	ms_setenv(const char *key, const char *value, int overwrite)
{
	t_env	*env;
	t_env	*new_env;

	env = g_env_root.next;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (overwrite != 0)
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			return (0);
		}
		env = env->next;
	}
	new_env = new_env_var(key, value);
	if (new_env == NULL)
	{
		fatal_error("malloc");
		return (-1);
	}
	new_env->next = g_env_root.next;
	g_env_root.next = new_env;
	return (0);
}

int	ms_unsetenv(const char *key)
{
	t_env	*prev_env;
	t_env	*env;

	prev_env = &g_env_root;
	env = g_env_root.next;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			prev_env->next = env->next;
			free(env);
			return (0);
		}
		prev_env = env;
		env = env->next;
	}
	return (0);
}
