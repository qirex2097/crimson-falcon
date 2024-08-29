/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:33:43 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:33:46 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
