/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:23:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/27 18:52:11 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	ft_printf("\n$> ");
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	//signal(SIGINT, &sigint);
	minishell(env);
	return (0);
}
