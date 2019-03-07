/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:24:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/07 13:56:38 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(char ***env)
{
	char	**tab;
	char	*tmp;
	char	*tmp2;
	int		i;

	tab = *env;
	i = 0;
	while (tab[i] && ft_strncmp(tab[i], "SHLVL=", 6) != 0)
		i++;
	if (tab[i])
	{
		tmp = tab[i];
		tmp2 = ft_itoa(ft_atoi(&tab[i][6]) + 1);
		tab[i] = ft_strjoin("SHLVL=", tmp2);
		free(tmp);
		free(tmp2);
	}
	else
	{
		create_variable(3, (tab = ft_strsplit("setenv SHLVL 1", ' ')), env);
		free_tab(tab);
	}
}

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

int		minishell(char **env)
{
	char	*buf;
	char	*tmp;
	char	**myenv;
	t_lexer	lexer;

	g_ret = 0;
	lexer.tokens = NULL;
	myenv = copy_env(env, 0);
	set_shlvl(&myenv);
	write(1, "\033[1;32m$> \033[0m", 14);
	while (get_next_line(0, &buf) == 1)
	{
		while (!fill_lexer(buf, &lexer, myenv))
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
			g_ret = parser(&lexer, &myenv);
			free_lexer(&lexer);
		}
		!g_ret ? write(1, "\033[1;32m$> \033[0m", 14) : write(1, "\033[1;31m$> \033[0m", 14);
	}
	free_tab(myenv);
	return (g_ret);
}
