/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:40:10 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/13 18:55:43 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_directory(char *path, char *display)
{
	struct stat	fstat;

	stat(path, &fstat);
	if (!S_ISDIR(fstat.st_mode))
		return (error_exec(6, "cd", display, 0));
	return (1);
}

int		test_access(char *path)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 1;
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			i++;
		tmp = ft_strsub(path, 0, i);
		if (access(tmp, F_OK) == -1)
		{
			free(tmp);
			return (1);
		}
		else if (access(tmp, X_OK) == -1)
		{
			free(tmp);
			return (2);
		}
		free(tmp);
		if (path[i] == '/')
			i++;
	}
	return (0);
}

int		error_exec(int no, char *prog, char *display, int ret)
{
	if (no == 0)
		return (0);
	if (prog)
		write(2, prog, ft_strlen(prog));
	if (no == 1)
		ft_putstr_fd(": command not found: ", 2);
	else if (no == 2)
		ft_putstr_fd(": permission denied: ", 2);
	else if (no == 3)
		ft_putstr_fd(
			": Variable name must contain alphanumeric characters.", 2);
	else if (no == 4)
		ft_putstr_fd(": no such file or directory: ", 2);
	else if (no == 5)
		ft_putstr_fd(": Too many arguments. ", 2);
	else if (no == 6)
		ft_putstr_fd(": not a directory: ", 2);
	else if (no == 7)
		ft_putstr_fd(": illegal option -- ", 2);
	else if (no == 8)
		ft_putstr_fd("Invalid argument ", 2);
	if (display)
		write(2, display, ft_strlen(display));
	write(2, "\n", 1);
	return (ret);
}
