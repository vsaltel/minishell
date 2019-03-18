/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:15:36 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/18 14:31:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_arg(t_token *current, int *argc, char ***argv)
{
	t_token	*begin;
	int		ac;
	char	**av;

	begin = current;
	ac = 0;
	while (current && current->type == TOKEN_NAME)
	{
		ac++;
		current = current->next;
	}
	if (!(av = malloc(sizeof(char *) * (ac + 1))))
		exit(1);
	ac = 0;
	current = begin;
	while (current && current->type == TOKEN_NAME)
	{
		av[ac++] = ft_strdup(current->content);
		current = current->next;
	}
	current = begin;
	av[ac] = NULL;
	*argc = ac;
	*argv = av;
}

int			parser(t_shell *shell)
{
	t_token	*current;
	int		ret;
	int		argc;
	char	**argv;

	ret = 0;
	current = shell->lexer.tokens;
	while (current)
	{
		if (current->type == TOKEN_NAME)
		{
			set_arg(current, &argc, &argv);
			ret = execute(shell, argc, argv);
			free_tab(argv);
			while (--argc > -1)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (ret);
}
