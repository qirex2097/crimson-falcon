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

#include "minishell.h"

#define PROMPT  "minishell$ "

//----- ここからデバッグ用
void print_tokens(t_token *p)
{
	int i;
	while (p)
	{
		if (is_word(p)) {
			write(STDERR_FILENO, "w:>", 3);
			i = 0;
			while (p->token[i])
			{
				write(STDERR_FILENO, &p->token[i], 1);
				i++;
			}
			write(STDERR_FILENO, "<\n", 2);
		}
		else if (is_operator(p))
			printf("o:%s\n", p->token);
		p = p->next;
	}
}

void print_cmd(t_cmd *cmd)
{
	int i, j;
	t_redirect *redir;
	i = 0;
	while(cmd)
	{
		printf("print_cmd:i=%d\n", i);
		j = 0;
		while (cmd->args[j])
		{
			printf("%s", cmd->args[j]);
			if (cmd->args[j+1]) printf(",");
			j++;
		}
		printf("\n");
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->kind == ND_REDIR_OUT) {
				printf(">%s\n", redir->filename);
			} else if (redir->kind == ND_REDIR_IN) {
				printf("<%s\n", redir->filename);
			} else if (redir->kind == ND_REDIR_APPEND) {
				printf(">>%s\n", redir->filename);
			} else if (redir->kind == ND_REDIR_HEREDOC) {
				printf("<<%s\n", redir->filename);
			}
			redir = redir->next;
		}
		i++;
		cmd = cmd->next;
	}
}

void print_node(t_node *node)
{
	int i = 0;
	while(node)
	{
		printf("----- print_noode:i=%d\n", i);
		print_cmd(&node->command);
		node = node->next;
		i++;
	}
}

void print_env(t_env *env)
{
	int i = 0;
	while (env)
	{
		printf("%d:%s=%s\n", i, env->key, env->value);
		env = env->next;
		i++;
	}
}
//----- ここまでデバッグ用

int interpret(char *line, int prev_status)
{
	t_token *tokens;
	int status;
	t_node	*node;

	tokens = tokenizer(line);//トークンに分割
	// printf("%s$\n", line);
	// print_tokens(tokens);
	if (tokens == NULL)
	{
		return(0);
	}
	add_history(line);//トークンがなければ履歴に登録しない
	expand(tokens, prev_status);
	node = parse(tokens);
	status = exec(node);
	free_tokens(tokens);
	if (node)
		free_node(node);

    return(status);
}

// グローバル変数
t_env *g_env_root = NULL;
bool readline_interrupted = false;

int	main()
{
	char	*line;
	int	status = 0;

	rl_outstream = stderr;
	setup_signal();
	g_env_root = initialize_env();
	if (g_env_root == NULL)
		exit(1);
	while(1)
	{
		line = readline(PROMPT);
		if(!line)
			break;
		if(*line)
		{
			status = interpret(line, status);
		}
		free(line);
	}
	cleanup_env(g_env_root);
	exit(status);
}
