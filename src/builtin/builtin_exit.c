/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:32:28 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:32:34 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(char **argv)
{
	int	value;

	if (argv[1] == NULL)
		value = 0;
	else if (ft_isnum(argv[1]))
		value = atoi(argv[1]);
	else
		value = 255;
	exit(value);
	return (0);
}
