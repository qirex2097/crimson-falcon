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
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
}	t_node_kind;

typedef struct s_node t_node;
typedef struct s_r_node t_r_node;

struct s_r_node
{
	t_node_kind kind;
	t_r_node *next;
	// REDIR
	char	*filename;
};

struct s_node
{
	t_node_kind	kind;
	t_node	*next;
	// CMD
	char	**args;
	t_r_node  *redirects;
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

/*free.c*/
// void	free_tok(t_token *tok);
void	free_argv(char **argv);

/*tokenize.c*/
char	*skip_blank(char *line);
char	*skip_token(char *line);
void	expand(char **args);
char    *copy_token(char *start, char *end);
char	**tokenizer(char *line);

/*parse.c*/
t_node  *parse(char **tokens);

/*redirect.c*/
void open_redir_file(t_r_node *redir);
void do_redirect(t_r_node *redir);
void reset_redirect(t_r_node *redir);

#endif