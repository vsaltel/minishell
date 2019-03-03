/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:24:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/03 18:06:45 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(char **tab)
{
	char *tmp;
	char *tmp2;
	int i;
	int nb;

	nb = 1;
	i = 0;
	while (tab[i] && ft_strncmp(tab[i], "SHLVL=", 6) != 0)
		i++;
	nb += ft_atoi(&tab[i][6]);
	tmp = tab[i];
	tmp2 = ft_itoa(nb);
	tab[i] = ft_strjoin("SHLVL=", tmp2);
	free(tmp);
	free(tmp2);
}

char	**copy_env(char **env, int add_variable)
{
	char **tab;
	int i;

	i = 0;
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
	set_shlvl(tab);
	return (tab);
}

void	minishell(char **env)
{
	char *buf;
	char *tmp;
	char	**myenv;
	t_lexer lexer;

	lexer.tokens = NULL;
	myenv = copy_env(env, 0);
	write(1, "$> ", 3);
	while (get_next_line(0, &buf) == 1)
	{
		while (!fill_lexer(buf, &lexer))
		{
			free_lexer(&lexer);	
			write(1, "dquote> ", 9);
			tmp = buf;
			if (get_next_line(0, &buf) == 1)
				buf = ft_strjoin(tmp, buf);
			else
				exit (-1);
			free(tmp);
		}
		if (lexer.tokens)
		{
			set_lexer_env(&lexer, myenv);
			parser(&lexer, &myenv);
			free_lexer(&lexer);	
		}
		write(1, "$> ", 3);
	}
	free_tab(myenv);
}
