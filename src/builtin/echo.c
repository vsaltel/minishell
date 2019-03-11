/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:06:05 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/08 16:55:58 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		have_option(char *str, char c)
{
	int i;

	if (!str || str[0] != '-')
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

int		builtin_echo(int argc, char **argv, char ***envi, int lastret)
{
	int i;

	(void)envi;
	(void)lastret;
	if (argv && argc > 1)
	{
		i = 1;
		if (argv[i][0] == '-')
			i++;
		while (argv[i] && argv[i][0] == '\0')
			i++;
		if (argv[i])
			ft_printf("%s", argv[i]);
		while (argv[++i])
			ft_printf(" %s", argv[i]);
	}
	if (!have_option(argv[1], 'n'))
		ft_putchar('\n');
	return (0);
}
