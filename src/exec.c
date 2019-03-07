/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:09:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/07 15:24:44 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**get_path_env(char *file, char **env)
{
	int		i;
	char	*str;
	char	**tab;
	char	*tmp;

	if (!(str = get_env_variable("PATH", 4, env)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	tab = ft_strsplit(&str[i++], ':');
	i = -1;
	while (tab[++i])
	{
		tmp = tab[i];
		tab[i] = str_pathfile(tab[i], file);
		free(tmp);
	}
	return (tab);
}

static char		**get_path(char *file, char **env)
{
	char	**tab;
	int		i;

	i = ft_strlen(file);
	while (--i)
	{
		if (file[i] == '/')
			break ;
	}
	if (!i)
		return (get_path_env(file, env));
	else
	{
		if (!(tab = malloc(sizeof(char *) * 2)))
			exit(1);
		tab[0] = ft_strdup(file);
		tab[1] = NULL;
		return (tab);
	}
}

static int		new_process(char *str, char **argv, char **env)
{
	int		pid;
	int		ret;

	ret = -1;
	if ((pid = fork()) < 0)
		return (-1);
	if (!pid)
		execve(str, argv, env);
	else
		waitpid(pid, &ret, 0);
	return (ret);
}

static int		execute_other(char **argv, char **env)
{
	char	**tab;
	int		ret;
	int		i;

	if (!(tab = get_path(argv[0], env)))
		return (-1);
	ret = 1;
	i = -1;
	while (ret == 1 && tab[++i])
	{
		ret = test_access(tab[i]);
		if (!ret)
			return (new_process(tab[i], argv, env));
		else if (ret == 2)
			break ;
	}
	free_tab(tab);
	return (error_exec(ret, "minishell", argv[0], 128 - ret));
}

int				execute(int argc, char **argv, char ***env)
{
	const t_builtin	*list = g_builtin_list;
	int				i;

	i = -1;
	while (list[++i].name)
		if (ft_strcmp(list[i].name, argv[0]) == 0)
			return (list[i].function(argc, argv, env));
	return (execute_other(argv, *env));
}
