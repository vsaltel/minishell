/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:40:10 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/03 18:08:54 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	             test_access(char *path)
{
	char *tmp;
	int i;

	tmp = NULL;
	i = 1;
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			i++; 
		tmp = ft_strsub(path, 0, i);
		if (access(tmp, F_OK) == -1)
			return (1);
		else if (access(tmp, X_OK) == -1)
			return (2);
		free(tmp);
		if (path[i] == '/')
			i++;
	}
	return (0);
}

int	error_exec(int no, char *prog, char *display)
{
	if (no == 0)
		return (0);
	if (prog)
		write(2, prog, ft_strlen(prog));
	if (no == 1)
		write(2, ": command not found: ", 21);
	else if (no == 2)
		write(2, ": permission denied: ", 21);
	else if (no == 3)
		write(2, ": Variable name must contain alphanumeric characters: ", 54);
	else if (no == 4)
		write(2, ": no such file or directory: ", 29);
	write(2, display, ft_strlen(display));
	write(2, "\n", 1);
	return (-1);
}
