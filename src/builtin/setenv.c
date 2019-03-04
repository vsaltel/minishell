/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:08:41 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 15:26:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		existing_variable(int argc, char **argv, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
		if (true_variable(env[i], argv[1]))
		{
			tmp = env[i];
			env[i] = ft_strjoin(argv[1], "=");
			free(tmp);
			tmp = env[i];
			if (argc > 2)
			{
				env[i] = ft_strjoin(env[i], argv[2]);
				free(tmp);
			}
			return (1);
		}
	return (0);
}

void			create_variable(int argc, char **argv, char ***env)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = copy_env(*env, 1);
	i = 0;
	while (tab[i])
		i++;
	tab[i] = ft_strjoin(argv[1], "=");
	if (argc > 2)
	{
		tmp = tab[i];
		tab[i] = ft_strjoin(tmp, argv[2]);
		free(tmp);
	}
	tab[i + 1] = NULL;
	free_tab(*env);
	*env = tab;
}

int				builtin_setenv(int argc, char **argv, char ***envi)
{
	int		i;
	char	*tmp;
	char	**env;

	env = *envi;
	if (argc < 2)
		return (0);
	i = -1;
	while (argv[1][++i])
		if (!ft_isalnum(argv[1][i]))
			return (error_exec(3, "setenv", NULL));
	if (!existing_variable(argc, argv, env))
		create_variable(argc, argv, envi);
	return (0);
}
