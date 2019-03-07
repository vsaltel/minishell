/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:05:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/07 11:09:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_exit(int argc, char **argv, char ***envi)
{
	(void)argc;
	(void)argv;
	(void)envi;
	if (argc > 1)
		exit(atoi(argv[1]));
	exit(g_ret);
	return (0);
}
