/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:25:04 by kahori            #+#    #+#             */
/*   Updated: 2024/08/29 19:36:42 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define SHELL "minishell"

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
	ND_PIPELINE,
}							t_node_kind;

typedef struct s_cmd		t_cmd;
typedef struct s_redirect	t_redirect;
typedef struct s_node		t_node;

struct						s_redirect
{
	t_node_kind				kind;
	t_redirect				*next;
	// REDIR
	char					*filename;
	int						fd;
};

struct						s_cmd
{
	t_node_kind				kind;
	// CMD
	char					**args;
	t_redirect				*redir_out;
	t_redirect				*redir_in;
	// PIPE
	t_cmd					*next;
};

struct						s_node
{
	t_node_kind				kind;
	t_node					*next;
	t_cmd					command;
};

typedef enum
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_DELIMITER,
}							e_token_kind;

typedef struct s_token		t_token;
struct						s_token
{
	e_token_kind			kind;
	char					*token;
	t_token					*next;
};

typedef struct s_env		t_env;
struct						s_env
{
	char					*key;
	char					*value;
	t_env					*next;
};

/*main.c*/
extern bool					readline_interrupted;
extern t_env				g_env_root;

/*error.c*/
void						fatal_error(const char *msg);
void						assert_error(const char *msg);
void						err_exit(const char *location, const char *msg,
								int status);
void						ms_perror(const char *location);
void						ms_perror2(const char *msg, const char *msg2);
void						ms_perror3(const char *msg, const char *msg2,
								const char *msg3);
void						ms_perror_syntax(const char *msg, const char *msg2);

/*free.c*/
void						free_node(t_node *node);

/*tokenize.c*/
t_token						*tokenizer(char *line);
bool						is_command_line_operator(char *line);
void						free_tokens(t_token *tokens);
bool						is_word(t_token *token);
bool						is_operator(t_token *token);
bool						is_delimiter(t_token *token);
bool						is_pipe(t_token *token);

/* expand.c */
void						expand(t_token *tokens, int prev_status);
int	get_env_var_name_end(char *line);

/*parse.c*/
t_node						*parse(t_token *tokens);

/*redirect.c*/
int							open_redir_file(t_redirect *redir,
								t_redirect *heredoc);

/*builtin.c*/
int							is_builtin(char **argv);
int							exec_builtin_command(char **argv);

/*signal.c*/
void						setup_signal(void);
void						reset_signal(void);

/* exec.c */
char						*search_path(const char *filename);
int							exec(t_node *node);

/* environ.c */
t_env						*initialize_env(void);
void						cleanup_env(t_env *env_root);
char						**create_env_array(t_env *env_root);
const char					*ms_getenv(const char *key);
int							ms_setenv(const char *key, const char *value,
								int overwrite);
int							ms_unsetenv(const char *key);
bool						is_valid_env_name(const char *key);

/*libft.c*/
//後でlibft導入するので削除
char						*ft_strtrim(char const *s1, char const *set);
char						*ft_itoa(int i);
size_t						ft_strlen(const char *str);
char						*ft_strncpy(char *dst, const char *src, size_t len);
int							ft_strcmp(const char *s1, const char *s2);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strchr(const char *s, int c);
char						*ft_strdup(const char *s1);
char						*ft_strncat(char *s1, const char *s2, size_t n);
char *ft_strndup(const char *s1, size_t n);

#endif
