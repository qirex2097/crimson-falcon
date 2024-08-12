/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:48:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/24 22:05:25 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
print_argv(char **argv)
{
	int i;
	i = 0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	char *line = "ls -l >ttt.txt | grep c";
	char **tokens;
	t_node *node;
	int i;
	
	tokens = tokenizer(line);
	print_argv(tokens);
	node = parse(tokens);
	while (node) {
		print_argv(node->args);
		node = node->next;
	}
	return 0;
}
