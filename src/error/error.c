/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:51:23 by kahori            #+#    #+#             */
/*   Updated: 2024/07/31 07:50:44 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_PREFIX SHELL ": "

void	print_to_stderr(const char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		write(STDERR_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
}

void	fatal_error(const char *msg)
{
	const char	*args[] = {"Fatal Error: ", "1", "\n", NULL};

	args[1] = msg;
	print_to_stderr(args);
	exit(1);
}

void	assert_error(const char *msg)
{
	const char	*args[] = {"Assert Error: ", "1", "\n", NULL};

	args[1] = msg;
	print_to_stderr(args);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	ms_perror2(location, msg);
	exit(status);
}

void	ms_perror(const char *msg)
{
	const char	*args[] = {ERROR_PREFIX, "1", "\n", NULL};

	args[1] = msg;
	print_to_stderr(args);
}

void	ms_perror2(const char *msg, const char *msg2)
{
	const char	*args[] = {ERROR_PREFIX, "1", ": ", "3", "\n", NULL};

	args[1] = msg;
	args[3] = msg2;
	print_to_stderr(args);
}

void	ms_perror3(const char *msg, const char *msg2, const char *msg3)
{
	const char *args[] = {ERROR_PREFIX, "1", ": ", "`", "4", "'", ": ", "7",
		"\n", NULL};
	args[1] = msg;
	args[4] = msg2;
	args[7] = msg3;
	print_to_stderr(args);
}
