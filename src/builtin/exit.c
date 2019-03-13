/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:05:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/13 17:19:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, char **argv)
{
	free_tab(shell->env);
	free_tab(argv);
	free_lexer(&(shell->lexer));
}

int		test_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		builtin_exit(t_shell *shell, int argc, char **argv)
{
	int		ret;

	(void)argv;
	if (argc > 2)
		return (error_exec(5, "exit", NULL, 1));
	if (argc > 1)
	{
		if (test_char(argv[1]))
		{
			ret = atoi(argv[1]);
			free_shell(shell, argv);
			exit(ret);
		}
		else
		{
			ft_putstr_fd("exit: Expression Syntax.\n", 2);
			return (1);
		}
	}
	free_shell(shell, argv);
	exit(shell->lastret);
	return (0);
}
