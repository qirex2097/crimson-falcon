/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:43:22 by kahori            #+#    #+#             */
/*   Updated: 2024/07/21 08:44:37 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void heredoc_write(char *str, int fd)
{
	char *key;
	const char *value;
	char *p;
	int length;

	p = ft_strchr(str, '$');
	while (*str && (p != NULL && *(p + 1) != '\0'))
	{
		length = p - str;
		write(fd, str, length);
		length = get_env_var_name_end(p);
		key = ft_strndup(p + 1, length - 1);
		str = p + get_env_var_name_end(p);
		p = ft_strchr(str, '$');
		value = ms_getenv(key);
		if (value)
			write(fd, value, ft_strlen(value));
		free(key);
	}
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	heredoc_loop(const char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		readline_interrupted = false;
		line = readline("> ");
		if (line == NULL)
			break ;
		if (readline_interrupted == true || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (fd >= 0)
		{
			heredoc_write(line, fd);
		}
		free(line);
	}
	return ;
}

int	open_heredoc(const char *delimiter)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	readline_interrupted = false;
	heredoc_loop(delimiter, pfd[1]);
	close(pfd[1]);
	if (readline_interrupted)
	{
		close(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}
