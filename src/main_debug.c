#include "minishell.h"

/*
 * デバッグ用関数、リンク不要
 */

//----- ここからデバッグ用
void	print_tokens(t_token *p)
{
	int	i;

	while (p)
	{
		if (is_word(p))
		{
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

void	print_cmd(t_cmd *cmd)
{
	t_redirect	*redir;
	int			i;
	int			j;

	i = 0;
	while (cmd)
	{
		printf("print_cmd:i=%d\n", i);
		j = 0;
		while (cmd->args[j])
		{
			printf("%s", cmd->args[j]);
			if (cmd->args[j + 1])
				printf(",");
			j++;
		}
		printf("\n");
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->kind == ND_REDIR_OUT)
			{
				printf(">%s\n", redir->filename);
			}
			else if (redir->kind == ND_REDIR_IN)
			{
				printf("<%s\n", redir->filename);
			}
			else if (redir->kind == ND_REDIR_APPEND)
			{
				printf(">>%s\n", redir->filename);
			}
			else if (redir->kind == ND_REDIR_HEREDOC)
			{
				printf("<<%s\n", redir->filename);
			}
			redir = redir->next;
		}
		i++;
		cmd = cmd->next;
	}
}

void	print_node(t_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		printf("----- print_noode:i=%d\n", i);
		print_cmd(&node->command);
		node = node->next;
		i++;
	}
}

void	print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		printf("%d:%s=%s\n", i, env->key, env->value);
		env = env->next;
		i++;
	}
}
//----- ここまでデバッグ用

