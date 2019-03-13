/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:40:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/11 16:42:12 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct				s_shell
{
	char	**env;	
	t_lexer	lexer;
	int		lastret;
}							t_shell;

typedef struct			s_builtin
{
	char	*name;
	int		(*function)(t_shell *shell, int argc, char **argv);
}						t_builtin;

int						builtin_cd(t_shell *shell, int argc, char **argv);
int						builtin_exit(t_shell *shell, int argc, char **arg);
int						builtin_env(t_shell *shell, int argc, char **argv);
int						builtin_echo(t_shell *shell, int argc, char **argv);
int						builtin_setenv(t_shell *shell, int argc, char **argv);
int						builtin_unsetenv(t_shell *shell, int argc, char **argv);

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
