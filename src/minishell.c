/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:24:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/11 13:40:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env, int add_variable)
{
	char	**tab;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	if (!(tab = malloc(sizeof(char *) * (i + add_variable + 1))))
		exit(1);
	i = 0;
	while (env[i])
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int		minishell(char **env, t_shell shell)
{
	char	*buf;
	char	*tmp;
	t_lexer	lexer;
	int		lastret;

	shell.lastret = 0;
	lexer.tokens = NULL;
	write(1, "\033[1;32m$> \033[0m", 14);
	while (get_next_line(0, &buf) == 1)
	{
		while (!fill_lexer(buf, &lexer, env))
		{
			free_lexer(&lexer);
			write(1, "dquote> ", 9);
			tmp = buf;
			if (get_next_line(0, &buf) == 1)
				buf = ft_strjoin(tmp, buf);
			else
				exit(-1);
			free(tmp);
		}
		if (lexer.tokens)
		{
			free(buf);
			lastret = parser(&lexer, &env, lastret);
			free_lexer(&lexer);
		}
		!lastret ? write(1, "\033[1;32m$> \033[0m", 14) :
			write(1, "\033[1;31m$> \033[0m", 14);
	}
	free_tab(env);
	return (lastret);
}
