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

static void perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	assert_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}

void xperror(const char *location)
{
	perror_prefix();
	perror(location);
}