/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:24:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/12 14:51:45 by vsaltel          ###   ########.fr       */
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

int		minishell(t_shell *shell)
{
	char	*buf;
	char	*tmp;

	write(1, "\033[1;32m$> \033[0m", 14);
	while (get_next_line(0, &buf) == 1)
	{
		while (!fill_lexer(buf, shell))
		{
			free_lexer(&(shell->lexer));
			write(1, "dquote> ", 9);
			tmp = buf;
			get_next_line(0, &buf) == 1 ? buf = ft_strjoin(tmp, buf) : exit(-1);
			free(tmp);
		}
		if (shell->lexer.tokens)
		{
			free(buf);
			shell->lastret = parser(shell);
			free_lexer(&(shell->lexer));
		}
		!(shell->lastret) ? write(1, "\033[1;32m$> \033[0m", 14) :
			write(1, "\033[1;31m$> \033[0m", 14);
	}
	free_tab(shell->env);
	return (shell->lastret);
}
