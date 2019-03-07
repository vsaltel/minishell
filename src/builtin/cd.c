/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:07:06 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/07 16:33:35 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		change_oldpwd(char ***envi)
{
	int		j;
	char	*tmp;
	char	**env;
	char	*pwd;

	env = *envi;
	if ((pwd = get_env_variable("PWD", 3, env)))
	{
		j = 0;
		while (env[j] && ft_strncmp(env[j], "OLDPWD=", 7) != 0)
			j++;
		if (env[j])
		{
			tmp = env[j];
			env[j] = ft_strjoin("OLDPWD=", pwd + 4);
			free(tmp);
		}
		else
		{
			*envi = create_env_variable("OLDPWD", pwd + 4, env);
			free_tab(env);
		}
	}
}

static void		change_pwd(char ***envi)
{
	char	*tmp;
	char	*tmp2;
	char	**env;
	int		i;

	env = *envi;
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	tmp2 = getcwd(NULL, 0);
	if (env[i])
	{
		tmp = env[i];
		env[i] = ft_strjoin("PWD=", tmp2);
		free(tmp);
		free(tmp2);
	}
	else
	{
		*envi = create_env_variable("PWD", tmp2, env);
		free_tab(env);
	}
}

static int		cd_absolu(char **argv)
{
	char	*tmp;
	char	*tmp2;

	tmp = getcwd(NULL, 0);
	tmp2 = str_pathfile(tmp, argv[1]);
	if (!is_directory(tmp2, argv[1]))
		return (1);
	free(tmp);
	chdir(tmp2);
	free(tmp2);
	return (0);
}

static int		cd_other(char **argv, char **env)
{
	int		j;
	char	*tmp;

	j = 0;
	if (argv[1][0] == '-' && argv[1][1] == '\0')
		chdir(get_env_variable("OLDPWD", 6, env) + 7);
	else if (!(j = test_access(argv[1])))
	{
		if (argv[1][0] != '/')
			return (cd_absolu(argv) ? 1 : 0);
		else
		{
			if (!is_directory(argv[1], argv[1]))
				return (1);
			chdir(argv[1]);
		}
	}
	else
	{
		return (j == 1 ? error_exec(4, "cd", argv[1], 1) :
				error_exec(j, "cd", argv[1], 1));
	}
	return (0);
}

int				builtin_cd(int argc, char **argv, char ***envi)
{
	int		ret;
	int		i;
	char	**env;

	env = *envi;
	ret = 0;
	if (argc < 2)
		chdir(get_env_variable("HOME", 4, env) + 5);
	else
		ret = cd_other(argv, env);
	change_oldpwd(envi);
	change_pwd(envi);
	return (ret);
}
