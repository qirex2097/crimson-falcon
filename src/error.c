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

#define ERROR_PREFIX "minshell: "

size_t ft_strlen(const char *s) { return strlen(s); }//後で差し替え

void print_to_stderr(const char **args)
{
	int i;
	i = 0;
	while(args[i])
	{
		write(STDERR_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
}

void	fatal_error(const char *msg)
{
	const char *args[] = {"Fatal Error: ", "", "\n", NULL};
	args[1] = msg;
	print_to_stderr(args);
	exit(1);
}

void	assert_error(const char *msg)
{
	const char *args[] = {"Assert Error: ", "", "\n", NULL};
	args[1] = msg;
	print_to_stderr(args);
	exit(255);
}

void err_exit(const char *location, const char *msg, int status)
{
	const char *args[] = {ERROR_PREFIX, "", ": ", "", "\n", NULL};
	args[1] = location;
	args[3] = msg;
	print_to_stderr(args);
	exit(status);
}

void xperror(const char *msg)
{
	const char *args[] = {ERROR_PREFIX, "", "\n", NULL};
	args[1] = msg;
	print_to_stderr(args);
}