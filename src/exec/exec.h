/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exec_utils.c */
char	*search_path(const char *filename);
bool	is_command_not_found(const char *path);
bool	is_directory(const char *path);

/* exec_child.c */
void	exec_child_process(t_cmd *cmd, int prev_fd, int *pfd);

/* exec_builtin.c */
int		_exec_builtin_command(t_cmd *cmd, int prev_fd, int *pfd);
