/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:06:05 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/03 12:06:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(int argc, char **argv, char ***envi)
{
	(void)argc;
	(void)envi;
	int i;

	if (argv && argc > 1)
	{
		i = 1;
		ft_printf("%s", argv[i]);
		while (argv[++i])
			ft_printf(" %s", argv[i]);
	}
	ft_putchar('\n');
	return (0);
}