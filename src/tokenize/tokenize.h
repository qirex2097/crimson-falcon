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

char	*skip_token(char *line);
char	*skip_blank(char *line);
t_token	*append_token(char *start, char *end);
char	**get_operators(void);
char	*skip_token(char *line);
char	*skip_blank(char *line);
char	*skip_command_line_operator(char *line);
char	*skip_quate(char *p, char quote);

