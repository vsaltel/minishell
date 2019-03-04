/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:40:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 13:41:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int						builtin_cd(int argc, char **argv, char ***envi);
int						builtin_exit(int argc, char **argv, char ***envi);
int						builtin_env(int argc, char **argv, char ***envi);
int						builtin_echo(int argc, char **argv, char ***envi);
int						builtin_setenv(int argc, char **argv, char ***envi);
int						builtin_unsetenv(int argc, char **argv, char ***envi);

typedef struct			s_builtin
{
	char	*name;
	int		(*function)(int argc, char **argv, char ***envi);
}						t_builtin;

static const t_builtin	g_builtin_list[] =
{
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{"env", &builtin_env},
	{"exit", &builtin_exit},
	{NULL, NULL}
};

#endif
