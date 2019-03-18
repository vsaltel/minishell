/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:24:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/14 18:43:46 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_env(char **env, int add_variable)
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

static int	wait_quote(t_shell *shell, char **buf)
{
	char	*tmp;
	char	*tmp2;

	g_wait_quote = 1;
	free_lexer(&(shell->lexer));
	write(1, "quote> ", 8);
	tmp = *buf;
	if (get_next_line(0, &tmp2) == 1)
		*buf = ft_strjoin(tmp, tmp2);
	else if (g_wait_quote == 0)
	{
		free(tmp);
		*buf = NULL;
		ft_putchar('\n');
		return (0);
	}
	if (tmp2)
		free(tmp2);
	free(tmp);
	return (1);
}

int			minishell(t_shell *shell)
{
	char	*buf;

	write(1, "\033[1;32m$> \033[0m", 14);
	while (get_next_line(0, &buf) == 1)
	{
		while (!fill_lexer(buf, shell))
			if (!wait_quote(shell, &buf))
				break ;
		g_wait_quote = 0;
		if (shell->lexer.tokens)
		{
			free(buf);
			shell->lastret = parser(shell);
			free_lexer(&(shell->lexer));
		}
		else
			free(buf);
		!(shell->lastret) ? write(1, "\033[1;32m$> \033[0m", 14) :
			write(1, "\033[1;31m$> \033[0m", 14);
	}
	free_tab(shell->env);
	return (shell->lastret);
}
