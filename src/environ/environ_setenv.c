/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

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

bool	is_env_var_existed(const char *key, const char *value, int overwrite)
{
	t_env	*env;

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
			return (true);
		}
		env = env->next;
	}
	return (false);
}

int	ms_setenv(const char *key, const char *value, int overwrite)
{
	t_env	*new_env;

	if (is_env_var_existed(key, value, overwrite))
		return (0);
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
