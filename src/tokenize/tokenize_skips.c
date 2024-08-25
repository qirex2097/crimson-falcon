/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:45:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/31 08:27:39 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

char	*skip_command_line_operator(char *line)
{
	char	**operators;
	int		i;

	operators = get_operators();
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(operators[i], line, ft_strlen(operators[i])) == 0)
			return (line + ft_strlen(operators[i]));
		i++;
	}
	return (line);
}

char	*skip_blank(char *line)
{
	char	*current;

	current = line;
	while (*current == ' ' && *current)
		current++;
	return (current);
}

char	*skip_quate(char *p, char quote)
{
	if (*p != quote)
		return (p);
	p++;
	while (*p != quote && *p)
		p++;
	if (*p == quote)
		p++;
	else
	{
		ms_perror("unexpected EOF while looking for matching \'or\".");
		return (NULL);
	}
	return (p);
}
