/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:07:06 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 18:31:05 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		change_oldpwd(char *pwd, char **env)
{
	int j;
	char *tmp;

	if (pwd)
	{
		j = 0;
		while (env[j] && ft_strncmp(env[j], "OLDPWD=", 7) != 0)
			j++;
		tmp = env[j];
		env[j] = ft_strjoin("OLDPWD=", pwd + 4);
		free(tmp);
	}
}

static void		change_pwd(char **pwd)
{
	char *tmp;
	char *tmp2;

	if (*pwd)
	{
		tmp2 = getcwd(NULL, 0);
		tmp = *pwd;
		*pwd = ft_strjoin("PWD=", tmp2);
		free(tmp);
		free(tmp2);
	}
}

static void		cd_home(char *pwd, char **env)
{
	char	*tmp;
	int		j;

	j = 0;
	change_oldpwd(pwd, env);
	while (env[j] && ft_strncmp(env[j], "HOME=", 5) != 0)
		j++;
	env[j] ? chdir(env[j] + 5) : chdir("/");
}

static void		cd_other(char *pwd, char **argv, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = 0;
	if (!(j = test_access(argv[1])))
	{
		change_oldpwd(pwd, env); 
		if (argv[1][0] != '/')
		{
			tmp = getcwd(NULL, 0);
			tmp2 = str_pathfile(tmp, argv[1]);
			free(tmp);
			chdir(tmp2);
			free(tmp2);
		}
		else
			chdir(argv[1]);
	}
	else
		j == 1 ? error_exec(4, "cd", argv[1]) : error_exec(j, "cd", argv[1]);
}

int				builtin_cd(int argc, char **argv, char ***envi)
{
	int		i;
	char	**env;

	env = *envi;
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	if (argc < 2)
		cd_home(env[i], env);
	else
		cd_other(env[i], argv, env);
	change_pwd(&env[i]);
	return (0);
}
