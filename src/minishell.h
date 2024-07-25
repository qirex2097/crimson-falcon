/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:25:04 by kahori            #+#    #+#             */
/*   Updated: 2024/07/25 19:26:46 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_token		t_token;

enum						e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_kind	t_token_kind;

// `word` is zero terminated string.
struct						s_token
{
	char					*word;
	t_token_kind			kind;
	t_token					*next;
};

/*main.c*/
char	*search_path(const char *filename);
int		interpret(char *line);

/*error.c*/
void	fatal_error(const char *msg);
void	assert_error(const char *msg);

/*free.c*/
void	free_tok(t_token *tok);
void	free_argv(char **argv);

/*tokenize.c*/
char	*skip_blank(char *line);
char	*skip_token(char *line);
char	**tokenizer(char *line);

#endif