/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:05:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/08 14:46:37 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		builtin_exit(int argc, char **argv, char ***envi, int lastret)
{
	(void)argv;
	(void)envi;
	if (argc > 2)
		return (error_exec(5, "exit", NULL, 1));
	if (argc > 1)
	{
		if (test_char(argv[1]))
			exit(atoi(argv[1]));
		else
		{
			ft_putstr_fd("exit: Expression Syntax.\n", 2);
			return (1);
		}
	}
	exit(lastret);
	return (0);
}
