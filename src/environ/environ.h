/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:33:32 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:33:34 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* environ_ftlib.c */
int		ft_isalpha(int c);
int		ft_isalnum(int c);

/* environ.c */
t_env	*new_env_var(const char *key, const char *value);
