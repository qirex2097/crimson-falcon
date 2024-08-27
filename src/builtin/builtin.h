/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:51:23 by kahori            #+#    #+#             */
/*   Updated: 2024/07/31 07:50:44 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	builtin_dummy(char **argv);
/* builtin_cd.c */
int	builtin_cd(char **argv);
/* builtin_echo.c */
int	builtin_echo(char **argv);
/* builtin_export.c */
int	builtin_export(char **argv);
int	builtin_unset(char **argv);
int	builtin_env(char **argv);
/* builtin_exit.c */
int	builtin_exit(char **argv);

int	builtin_pwd(char **argv);
