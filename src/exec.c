/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:09:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/14 18:48:16 by vsaltel          ###   ########.fr       */
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

static char		**get_tab_path(char *file, char **env)
{
	char	**tab;
	int		i;

	if (!(i = ft_strlen(file)))
		return (NULL);
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

char			*get_string_path(int *ret, char **argv, char **env)
{
	char	**tab;
	char	*str;
	int		i;

	*ret = 1;
	if (!(tab = get_tab_path(argv[0], env)))
		return (NULL);
	i = -1;
	while (*ret == 1 && tab[++i])
	{
		*ret = test_access(tab[i]);
		if (!(*ret))
		{
			str = ft_strdup(tab[i]);
			free_tab(tab);
			return (str);
		}
		else if (*ret == 2)
			break ;
	}
	free_tab(tab);
	return (NULL);
}

static int		new_process(char *str, char **argv, char **env)
{
	int		ret;

	ret = -1;
	if ((g_pid = fork()) < 0)
		return (-1);
	if (!g_pid)
		execve(str, argv, env);
	else
		waitpid(g_pid, &ret, 0);
	g_pid = 0;
	return (ret);
}

int				execute(t_shell *shell, int argc, char **argv)
{
	const t_builtin	*list = g_builtin_list;
	int				i;
	int				ret;
	char			*str;

	i = -1;
	while (list[++i].name)
		if (ft_strcmp(list[i].name, argv[0]) == 0)
			return (list[i].function(shell, argc, argv));
	ret = 0;
	if ((str = get_string_path(&ret, argv, shell->env)))
	{
		if (!is_dir(&ret, str, argv[0]))
			ret = new_process(str, argv, shell->env);
		free(str);
	}
	else
		return (error_exec(ret, "minishell", argv[0], 128 - ret));
	return (ret);
}
