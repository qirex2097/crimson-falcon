/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:28:55 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:36:37 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

// プロンプトの定義 "minishell$ "
#define PROMPT SHELL "$ "

// グローバル変数
t_env	g_env_root;
bool	readline_interrupted = false;
bool	main_loop_readline;

int	interpret(char *line, int prev_status)
{
	t_token	*tokens;
	int		status;
	t_node	*node;

	tokens = tokenizer(line); //トークンに分割
	if (tokens == NULL)
	{
		return (0);
	}
	add_history(line); //トークンがなければ履歴に登録しない
	expand(tokens, prev_status);
	node = parse(tokens);
	status = exec(node);
	free_tokens(tokens);
	if (node)
		free_node(node);
	return (status);
}

int	main_loop(void)
{
	char	*line;
	int		status;

	status = 0;
	while (1)
	{
		main_loop_readline = true;
		line = readline(PROMPT);
		main_loop_readline = false;
		if (!line)
			break ;
		else if (*line)
			status = interpret(line, status);
		free(line);
	}
	return (status);
}

int	main(int argc, char **argv)
{
	int	status;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	setup_signal();
	g_env_root.next = initialize_env();
	if (g_env_root.next == NULL)
		exit(1);
	ms_setenv("SHELL", argv[0], 1);
	status = main_loop();
	cleanup_env(g_env_root.next);
	exit(status);
}
