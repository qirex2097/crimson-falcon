/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

int	get_env_var_name_end(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '$' && is_alpha_under(line[1]))
	{
		return (0);
	}
	i = 1;
	while (is_alpha_under_number(line[i]))
		i++;
	return (i);
}

int	set_env_var_value(char *new_line, char *line, int length)
{
	char		env_var_name[LINE_MAX];
	const char	*env_var_value;

	ft_strncpy(env_var_name, line, length - 1);
	env_var_name[length - 1] = '\0';
	env_var_value = ms_getenv(env_var_name);
	if (env_var_value != NULL)
	{
		ft_strncpy(new_line, env_var_value, ft_strlen(env_var_value));
		return (ft_strlen(env_var_value));
	}
	return (0);
}

//end = 環境変数名の最後の位置
void	replace_env_var(char *new_line, char *line, int *pi, int *pj)
{
	int	end;

	end = get_env_var_name_end(&line[*pi]);
	if (end > 0)
	{
		*pj += set_env_var_value(&new_line[*pj], &line[*pi + 1], end);
		*pi = *pi + end - 1;
	}
	else
	{
		new_line[(*pj)++] = line[*pi];
	}
}

int	replace_exit_status_var(char *new_line, int status, int *pi, int *pj)
{
	char	*num_str;
	int		length;

	num_str = ft_itoa(status);
	ft_strncpy(&new_line[*pj], num_str, ft_strlen(num_str));
	length = ft_strlen(num_str);
	*pj += length;
	(*pi)++;
	free(num_str);
	return (length);
}
