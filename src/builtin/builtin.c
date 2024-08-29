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
#include "builtin.h"

int	is_builtin(char **argv)
{
	char	*command;
	char	*builtin_list[9];
	int		i;

	builtin_list[0] = "";
	builtin_list[1] = "cd";
	builtin_list[2] = "echo";
	builtin_list[3] = "env";
	builtin_list[4] = "pwd";
	builtin_list[5] = "export";
	builtin_list[6] = "unset";
	builtin_list[7] = "exit";
	builtin_list[8] = NULL;
	command = argv[0];
	i = 1;
	while (builtin_list[i])
	{
		if (ft_strcmp(builtin_list[i], command) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	exec_builtin_command(char **argv)
{
	int	builtin_no;
	int	status;
	int	(*builtin_func[9])(char **);

	builtin_func[0] = builtin_dummy;
	builtin_func[1] = builtin_cd;
	builtin_func[2] = builtin_echo;
	builtin_func[3] = builtin_env;
	builtin_func[4] = builtin_pwd;
	builtin_func[5] = builtin_export;
	builtin_func[6] = builtin_unset;
	builtin_func[7] = builtin_exit;
	builtin_func[8] = NULL;
	builtin_no = is_builtin(argv);
	status = builtin_func[builtin_no](argv);
	return (status);
}

int	builtin_dummy(char **argv)
{
	printf("builtin_dummy:%s\n", argv[0]);
	return (0);
}

int	builtin_pwd(char **argv)
{
	char	buff[PATH_MAX];

	(void)argv;
	if (getcwd(buff, PATH_MAX) == NULL)
	{
		ms_perror(argv[0]);
		return (-1);
	}
	write(STDOUT_FILENO, buff, ft_strlen(buff));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
