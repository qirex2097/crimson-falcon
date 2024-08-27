/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:51:23 by kahori            #+#    #+#             */
/*   Updated: 2024/07/31 07:50:44 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_n_option(const char *argv)
{
	size_t	i;

	if (ft_strncmp(argv, "-n", 2) != 0)
		return (false);
	i = 2;
	while (argv[i] != '\0')
	{
		if (argv[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(char **argv)
{
	size_t	i;
	bool	print_newline;

	i = 1;
	print_newline = true;
	while (argv[i] && check_n_option(argv[i]))
	{
		print_newline = false;
		i++;
	}
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (print_newline == true)
		write(1, "\n", 1);
	return (0);
}
