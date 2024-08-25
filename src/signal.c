/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:23:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	sigint_handler(int sig)
{
	(void)sig;
	readline_interrupted = true;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	setup_signal(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		fatal_error("signal");
	}
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		fatal_error("signal");
	}
}

void	reset_signal(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		fatal_error("signal");
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		fatal_error("signal");
	}
}
