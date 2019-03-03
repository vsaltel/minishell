/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:06:41 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/03 12:06:57 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(int argc, char **argv, char ***envi)
{
	(void)argc;
	(void)argv;
	char **env;
	int	i;

	env = *envi;
	if (!(env && *env))
		return (-1);
	i = 0;
	ft_putstr(env[i]);
	while (env[++i])
		ft_printf("\n%s", env[i]);
	ft_putchar('\n');
	return (0);
}