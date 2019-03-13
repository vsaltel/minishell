/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:06:41 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/13 18:53:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (error_exec(8, "env: ", "=", 1));
	return (0);
}

int			env_exec(t_shell *shell, t_shell *new, char **argv, int i)
{
	char	*tmp;
	int		ret;
	int		newargc;

	newargc = 0;
	while (argv[i + newargc])
		newargc++;
	ret = 0;
	if (!get_env_variable("PATH", 4, new->env))
	{
		tmp = argv[i];
		if (!(argv[i] = get_string_path(&ret, &argv[i], shell->env)))
			ret = error_exec(4, "env", tmp, 127);
		else
			ret = execute(new, newargc - i, &argv[i]);
		free(argv[i]);
		argv[i] = tmp;
	}
	else
		ret = execute(new, newargc - i, &argv[i]);
	return (ret);
}

int			builtin_env(t_shell *shell, int argc, char **argv)
{
	t_shell	new;
	int		i;
	int		ret;

	new.env = copy_env(shell->env, 0);
	new.lastret = shell->lastret;
	if (!(new.env && *(new.env)))
		return (-1);
	i = 1;
	if (i < argc)
		if ((ret = set_tmp_var(&i, argc, argv, &(new.env))))
		{
			free_tab(new.env);
			return (ret);
		}
	if (i < argc)
		ret = env_exec(shell, &new, argv, i);
	else
		display_env(new.env, &ret);
	free_tab(new.env);
	return (ret);
}
