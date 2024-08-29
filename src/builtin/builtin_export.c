/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:32:40 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:32:45 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv)
{
	t_env	*env;

	(void)argv;
	env = g_env_root.next;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_export_loop(char **argv)
{
	char	*equals;
	char	key[1024];
	char	value[1024];
	int		i;

	i = 1;
	while (argv[i])
	{
		equals = ft_strchr(argv[i], '=');
		if (equals != NULL)
		{
			ft_strncpy(key, argv[i], equals - argv[i]);
			key[equals - argv[i]] = '\0';
			ft_strncpy(value, equals + 1, ft_strlen(equals + 1) + 1);
			if (!is_valid_env_name(key))
			{
				ms_perror3(argv[0], argv[i], "not a valid identifier");
				return (1);
			}
			ms_setenv(key, value, 1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(char **argv)
{
	(void)argv;
	if (argv[1] == NULL)
		return (builtin_env(NULL));
	else
		return (builtin_export_loop(argv));
}

int	builtin_unset(char **argv)
{
	int	i;

	(void)argv;
	if (argv[1] == NULL)
	{
		return (0);
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			if (!is_valid_env_name(argv[i]))
			{
				ms_perror3(argv[0], argv[i], "not a valid identifier");
				return (1 * 256);
			}
			ms_unsetenv(argv[i]);
			i++;
		}
	}
	return (0);
}
