/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:25:04 by kahori            #+#    #+#             */
/*   Updated: 2024/07/19 16:42:08 by kahori           ###   ########.fr       */
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

//--------------------tokenize.c--------------------
t_token						*new_token(char *word, t_token_kind kind);
bool						is_blank(char c);
bool						consume_blank(char **rest, char *line);
bool						startswith(const char *s, const char *keyword);
bool						is_operator(const char *s);
bool						is_metacharacter(char c);
bool						is_word(const char *s);
//t_token						*operator(char **rest, char *line);
t_token						*word(char **rest, char *line);
t_token						*tokenize(char *line);
char						**tail_recursive(t_token *tok, int nargs,
								char **argv);
char						**token_list_to_argv(t_token *tok);

#endif