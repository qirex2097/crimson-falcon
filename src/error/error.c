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

#include "error.h"
#include "minishell.h"

void	err_exit(const char *location, const char *msg, int status)
{
	ms_perror2(location, msg);
	exit(status);
}

void	ms_perror(const char *msg)
{
	const char	*args[] = {": ", "1", "\n", NULL};

	args[1] = msg;
	print_to_stderr(args);
}

void	ms_perror2(const char *msg, const char *msg2)
{
	const char	*args[] = {": ", "1", ": ", "3", "\n", NULL};

	args[1] = msg;
	args[3] = msg2;
	print_to_stderr(args);
}

void	ms_perror3(const char *msg, const char *msg2, const char *msg3)
{
	const char	*args[10];

	args[0] = ": ";
	args[1] = msg;
	args[2] = ": ";
	args[3] = "`";
	args[4] = msg2;
	args[5] = "'";
	args[6] = ": ";
	args[7] = msg3;
	args[8] = "\n";
	args[9] = NULL;
	print_to_stderr(args);
}

void	ms_perror_syntax(const char *msg, const char *msg2)
{
	const char	*args[] = {": ", "1", "`", "3", "'\n", NULL};

	args[1] = msg;
	args[3] = msg2;
	print_to_stderr(args);
}
