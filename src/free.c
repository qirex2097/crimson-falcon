/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:43:22 by kahori            #+#    #+#             */
/*   Updated: 2024/07/21 08:44:37 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

/*------free-------*/
void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
		free(tok->word);
	free_tok(tok->next);
	free(tok);
}


void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
/*--------------*/