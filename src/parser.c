/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:15:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/11 17:48:50 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_arg(t_lexer *lexer, int *argc, char ***argv)
{
	t_token	*begin;
	int		ac;
	char	**av;

	begin = lexer->tokens;
	ac = 0;
	while (lexer->tokens && lexer->tokens->type == TOKEN_NAME)
	{
		ac++;
		lexer->tokens = lexer->tokens->next;
	}
	if (!(av = malloc(sizeof(char *) * (ac + 1))))
		exit(1);
	ac = 0;
	lexer->tokens = begin;
	while (lexer->tokens && lexer->tokens->type == TOKEN_NAME)
	{
		av[ac++] = lexer->tokens->content;
		lexer->tokens = lexer->tokens->next;
	}
	av[ac] = NULL;
	*argc = ac;
	*argv = av;
}

int		parser(t_shell *shell)
{
	t_token	*begin;
	int		ret;
	int		argc;
	char	**argv;

	ret = 0;
	begin = shell->lexer.tokens;
	while (shell->lexer.size > 0)
	{
		if (shell->lexer.tokens->type == TOKEN_NAME)
		{
			set_arg(&(shell->lexer), &argc, &argv);
			ret = execute(shell, argc, argv);
			shell->lexer.size -= argc;
			free(argv);
		}
		else
		{
			shell->lexer.tokens = shell->lexer.tokens->next;
			shell->lexer.size--;
		}
	}
	shell->lexer.tokens = begin;
	return (ret);
}
