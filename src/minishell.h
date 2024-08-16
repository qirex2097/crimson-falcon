/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:25:04 by kahori            #+#    #+#             */
/*   Updated: 2024/08/05 20:36:25 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

extern bool readline_interrupted;

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
	ND_PIPELINE,
}	t_node_kind;

typedef struct s_cmd t_cmd;
typedef struct s_redirect t_redirect;
typedef struct s_node t_node;

struct s_redirect
{
	t_node_kind kind;
	t_redirect *next;
	// REDIR
	char	*filename;
	int		fd;
};

# define TOKEN_MAX	100

struct s_cmd
{
	t_node_kind	kind;
	// CMD
	char	**args;
	t_redirect  *redirects;
	// PIPE
	t_cmd *next;
};

struct s_node
{
	t_node_kind kind;
	t_node *next;
	t_cmd command;
};


/*libft.c*/
//後でlibft導入するので削除
char	*ft_strtrim(char const *s1, char const *set);

/*main.c*/
char	*search_path(const char *filename);
int		interpret(char *line);

/*error.c*/
void	fatal_error(const char *msg);
void	assert_error(const char *msg);
void	err_exit(const char *location, const char *msg, int status);
void	xperror(const char *location);

/*free.c*/
// void	free_tok(t_token *tok);
void	free_argv(char **argv);
void free_node(t_node *node);

/*tokenize.c*/
void	expand(char **args);
char	**tokenizer(char *line);
bool is_command_line_operator(char *line);

/*parse.c*/
t_node  *parse(char **tokens);

/*redirect.c*/
int open_redir_file(t_redirect *redir);

/*builtin.c*/
int is_builtin(char **argv);
int exec_builtin_command(char **argv);

/*signal.c*/
void setup_signal(void);
void reset_signal(void);


#endif