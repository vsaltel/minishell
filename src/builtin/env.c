/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:06:41 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/08 16:21:10 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_env(char **env, int *ret)
{
	int i;

	i = 0;
	if (env[i])
	{
		ft_putstr(env[i]);
		while (env[++i])
			ft_printf("\n%s", env[i]);
		ft_putchar('\n');
	}
	*ret = 0;
}

static int	have_option(char *str)
{
	int i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'u')
			return (2);
		if (str[i] == 'i')
			return (3);
		else
			return (error_exec(7, "env", &str[i], 0));
	}
	return (1);
}

char		**create_var(char *var, char **env)
{
	int		i;
	char	**tab;

	if (!var)
		return (NULL);
	tab = copy_env(env, 1);
	i = 0;
	while (tab[i])
		i++;
	tab[i] = ft_strdup(var);
	tab[i + 1] = NULL;
	free_tab(env);
	return (tab);
}

int			set_tmp_var(int *i, int argc, char **argv, char ***env)
{
	int		ret;

	while (*i < argc && argv[*i][0] == '-' && argv[*i][1] != '-')
	{
		if (!(ret = have_option(argv[*i])))
			return (3);
		else if (ret == 2)
			*env = delete_env_variable(argv[++(*i)], *env);
		else if (ret == 3)
		{
			free_tab(*env);
			if (!(*env = malloc(sizeof(char *))))
				return (2);
			(*env)[0] = NULL;
		}
		*i += 1;
	}
	while (*i < argc && ft_strchr(argv[*i], '='))
		if (argv[(*i)++][0] != '=')
			*env = create_var(argv[(*i) - 1], *env);
		else
			return (error_exec(8, "env: setenv: ", "=", 1));
	return (0);
}

int			builtin_env(int argc, char **argv, char ***envi, int lastret)
{
	char	**env;
	int		i;
	int		ret;

	env = copy_env(*envi, 0);
	if (!(env && *env))
		return (-1);
	i = 1;
	if (i < argc)
		if ((ret = set_tmp_var(&i, argc, argv, &env)))
		{
			free_tab(env);
			return (ret);
		}
	if (i < argc)
	{
		if (!get_env_variable("PATH", 4, env))
		{
			argv[i] = get_string_path(&ret, &argv[i], *envi);
			ft_printf("la %s\n", argv[i]);
			ret = execute(argc - i, &argv[i], &env, lastret);
			free(argv[i]);
		}
		else
			ret = execute(argc - i, &argv[i], &env, lastret);
	}
	else
		display_env(env, &ret);
	free_tab(env);
	return (ret);
}
