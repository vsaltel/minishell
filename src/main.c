/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:23:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/13 14:59:11 by vsaltel          ###   ########.fr       */
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

int		main(int argc, char **argv, char **env)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.lastret = 0;
	shell.lexer.tokens = NULL;
	shell.env = copy_env(env, 0);
	set_shlvl(&(shell.env));
	return (minishell(&shell));
}
