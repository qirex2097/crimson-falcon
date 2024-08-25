/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	ft_bzero(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}

char	*search_path_loop(const char *filename, const char *value, char *end)
{
	char	*dup;
	char	path[PATH_MAX];

	ft_bzero(path, PATH_MAX);
	end = ft_strchr(value, ':');
	if (end)
		ft_strncpy(path, value, end - value);
	else
	{
		ft_strncpy(path, value, PATH_MAX - 1);
		path[PATH_MAX - 1] = '\0';
	}
	ft_strncat(path, "/", PATH_MAX - 1);
	path[PATH_MAX - 1] = '\0';
	ft_strncat(path, filename, PATH_MAX - 1);
	path[PATH_MAX - 1] = '\0';
	if (access(path, X_OK) == 0)
	{
		dup = ft_strdup(path);
		if (dup == NULL)
			fatal_error("strdup");
		return (dup);
	}
	return (NULL);
}

// TODO search_pathを書き換える！
char	*search_path(const char *filename)
{
	const char	*value;
	char		*end;
	char		*dup;

	value = ms_getenv("PATH");
	while (value && *value)
	{
		end = ft_strchr(value, ':');
		dup = search_path_loop(filename, value, end);
		if (dup)
			return (dup);
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

bool	is_command_not_found(const char *path)
{
	return (path == NULL || access(path, F_OK | X_OK) < 0);
}

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}
