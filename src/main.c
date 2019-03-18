/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:23:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/14 18:36:54 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_sig(int sig)
{
	(void)sig;
	if (g_wait_quote)
	{
		g_wait_quote = 0;
		ioctl(0, TIOCSTI, "\4\0");
	}
	else if (!g_pid)
	{
		write(1, "\n\033[1;31m$> \033[0m", 15);
		g_pid = 0;
	}
}

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

	g_pid = 0;
	g_wait_quote = 0;
	signal(SIGINT, my_sig);
	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.lastret = 0;
	shell.lexer.tokens = NULL;
	shell.lexer.size = 0;
	shell.env = copy_env(env, 0);
	set_shlvl(&(shell.env));
	return (minishell(&shell));
}
