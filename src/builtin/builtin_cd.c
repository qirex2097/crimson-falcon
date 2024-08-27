/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:51:23 by kahori            #+#    #+#             */
/*   Updated: 2024/07/31 07:50:44 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	set_oldpwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == 0)
		ms_perror("cd");
	else
		ms_setenv("OLDPWD", buff, 1);
}

int	builtin_cd(char **argv)
{
	char	buff[PATH_MAX];

	set_oldpwd();
	if (argv[1] == NULL)
	{
		if (ms_getenv("HOME") == NULL)
		{
			ms_perror2("cd", "HOME not set");
			return (1 * 256);
		}
		if (chdir(ms_getenv("HOME")) == -1)
		{
			ms_perror("cd");
			return (1 * 256);
		}
	}
	else
	{
		if (chdir(argv[1]) == -1)
			ms_perror("cd");
	}
	if (getcwd(buff, PATH_MAX) == 0)
		ms_perror("cd");
	ms_setenv("PWD", buff, 1);
	return (0);
}
