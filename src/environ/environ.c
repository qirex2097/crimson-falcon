/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

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
	int length;
	char	*key;
	char	*value;
	t_env *new_env;

	length = end - start;
	key = malloc(length + 1);
	value = malloc(ft_strlen(end) + 1);

	ft_strncpy(key, start, end - start);
	key[end - start] = '\0';
	ft_strncpy(value, end + 1, ft_strlen(end + 1) + 1);
	new_env = new_env_var(key, value);
	free(key);
	free(value);
	return (new_env);
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
