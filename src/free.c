/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:44:55 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/18 10:46:24 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_token	*tmp;

	while (lexer->tokens)
	{
		tmp = lexer->tokens->next;
		free(lexer->tokens->content);
		free(lexer->tokens);
		lexer->tokens = tmp;
	}
	lexer->tokens = NULL;
}

void	free_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
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
