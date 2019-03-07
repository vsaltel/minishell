/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:15:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/05 19:25:51 by vsaltel          ###   ########.fr       */
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

int		parser(t_lexer *lexer, char ***env)
{
	t_token	*begin;
	int		ret;
	int		argc;
	char	**argv;

	ret = 0;
	begin = lexer->tokens;
	while (lexer->size > 0)
	{
		if (lexer->tokens->type == TOKEN_NAME)
		{
			set_arg(lexer, &argc, &argv);
			ret = execute(argc, argv, env);
			lexer->size -= argc;
			free(argv);
		}
		else
		{
			lexer->tokens = lexer->tokens->next;
			lexer->size--;
		}
	}
	lexer->tokens = begin;
	return (ret);
}
