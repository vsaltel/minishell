/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:08:41 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/12 14:07:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		true_variable(char *env, char *arg)
{
	int j;

	j = 0;
	while (arg[j])
		j++;
	if (ft_strncmp(env, arg, ft_strlen(arg)) == 0 && env[j] == '=')
		return (1);
	return (0);
}

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

char			**create_variable(int argc, char **argv, char ***env)
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
	return (&tab[i]);
}

int				builtin_setenv(t_shell *shell, int argc, char **argv)
{
	int		i;

	if (argc < 2)
		return (builtin_env(shell, argc, argv));
	if (argc > 3)
		return (error_exec(5, "setenv", NULL, 0));
	i = -1;
	while (argv[1][++i])
		if (!ft_isalnum(argv[1][i]))
			return (error_exec(3, "setenv", NULL, -1));
	if (!existing_variable(argc, argv, shell->env))
		create_variable(argc, argv, &(shell->env));
	return (0);
}
