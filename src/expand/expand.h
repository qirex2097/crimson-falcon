/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* expand_utils.c */
bool	is_alpha(char ch);
bool	is_digit(char ch);
bool	is_alpha_under(char ch);
bool	is_alpha_under_number(char ch);
/* expand_env_var.c */
int		get_env_var_name_end(char *line);
int		set_env_var_value(char *new_line, char *line, int length);
void	replace_env_var(char *new_line, char *line, int *pi, int *pj);
int		replace_exit_status_var(char *new_line, int status, int *pi, int *pj);
