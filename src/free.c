/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:29:45 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/27 16:02:11 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_token	*tmp;

	while (lexer->tokens)
	{
		tmp = lexer->tokens->next;
		free(lexer->tokens);
		lexer->tokens = tmp;
	}
	lexer->tokens = NULL;
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = 0;
		i++;
	}
	free(tab);
	tab = 0;
}