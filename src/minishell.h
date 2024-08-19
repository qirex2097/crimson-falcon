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

typedef enum {
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_DELIMITER,
} e_token_kind;

typedef struct s_token t_token;
struct s_token {
	e_token_kind kind;
	char *token;
	t_token *next;
};

/*libft.c*/
//後でlibft導入するので削除
char	*ft_strtrim(char const *s1, char const *set);
char *ft_itoa(int i);

/*main.c*/

/*error.c*/
void	fatal_error(const char *msg);
void	assert_error(const char *msg);
void	err_exit(const char *location, const char *msg, int status);
void	xperror(const char *location);

/*free.c*/
void free_node(t_node *node);

/*tokenize.c*/
t_token	*tokenizer(char *line);
bool is_command_line_operator(char *line);
void free_tokens(t_token *tokens);
bool is_word(t_token *token);
bool is_operator(t_token *token);
bool is_delimiter(t_token *token);
bool is_pipe(t_token *token);

/* expand.c */
void	expand(t_token *tokens, int prev_status);

/*parse.c*/
t_node  *parse(t_token *tokens);

/*redirect.c*/
int open_redir_file(t_redirect *redir);

/*builtin.c*/
int is_builtin(char **argv);
int exec_builtin_command(char **argv);

/*signal.c*/
void setup_signal(void);
void reset_signal(void);

/* exec.c */
char	*search_path(const char *filename);
int exec(t_node *node);


#endif