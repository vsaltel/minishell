/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:06:05 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/12 17:25:23 by vsaltel          ###   ########.fr       */
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

int		builtin_echo(t_shell *shell, int argc, char **argv)
{
	int i;

	(void)shell;
	if (argv && argc > 1)
	{
		i = 1;
		if (argv[i][0] == '-' && argv[i][1] == 'n')
			i++;
		if (argv[i])
			ft_printf("%s", argv[i++]);
		while (argv[i])
			ft_printf(" %s", argv[i++]);
	}
	if (!have_option(argv[1], 'n'))
		ft_putchar('\n');
	return (0);
}
