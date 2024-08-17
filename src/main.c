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

void print_tokens(t_token *p)
{
	while (p)
	{
		if (is_word(p))
			printf("w:>%s<\n", p->token);
		else if (is_operator(p))
			printf("o:%s\n", p->token);
		p = p->next;
	}
}

int interpret(char *line)
{
	t_token *tokens;
	int status;
	t_node	*node;
	
	tokens = tokenizer(line);//トークンに分割
	if (tokens == NULL) 
	{
		return(0);
	}
	add_history(line);//トークンがなければ履歴に登録しない
	print_tokens(tokens);
	printf("expand\n");
	expand(tokens);
	// node = parse(tokens);
	// status = exec(node);
	print_tokens(tokens);
	free_tokens(tokens);
	node = NULL;//debug
	status = 0;//debug
	if (node)
		free_node(node);

    return(status);
}

int	main()
{
	char	*line;
	int	status = 0;

	rl_outstream = stderr;
	setup_signal();
	while(1)
	{
		line = readline("m42$ ");
		if(!line)		
			break; 
		if(*line) 
		{
			status = interpret(line);
		}
		free(line);
	}
	exit(status);
}
