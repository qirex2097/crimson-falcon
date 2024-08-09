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

# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <unistd.h>

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,
}	t_node_kind;

typedef struct s_node t_node;

struct s_node
{
	t_node	*next;
	t_node_kind	kind;
	char	**args;
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


#endif