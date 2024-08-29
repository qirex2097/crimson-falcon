/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:33:18 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:33:20 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

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
