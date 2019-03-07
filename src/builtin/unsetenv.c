/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:08:04 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/07 12:06:55 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**new_env(int nb, int argc, char **argv, char **env)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (env[i])
		i++;
	if (!(tab = malloc(sizeof(char *) * (i + 1 - nb))))
		return (NULL);
	i = 0;
	k = 0;
	while (env[i])
	{
		j = 0;
		while (++j < argc)
			if (env[i] && ft_strncmp(env[i], argv[j], ft_strlen(argv[j])) == 0
					&& env[i][ft_strlen(argv[j])] == '=')
				break ;
		if (j == argc)
			tab[k++] = ft_strdup(env[i]);
		i++;
	}
	tab[k] = NULL;
	return (tab);
}

int			builtin_unsetenv(int argc, char **argv, char ***envi)
{
	char	**env;
	int		nb;
	int		i;
	int		j;

	env = *envi;
	nb = 0;
	j = 1;
	while (j < argc)
	{
		i = -1;
		while (env[++i])
		{
			if (env[i] && ft_strncmp(env[i], argv[j], ft_strlen(argv[j])) == 0
					&& env[i][ft_strlen(argv[j])] == '=')
				nb++;
		}
		j++;
	}
	if (nb > 0)
	{
		*envi = new_env(nb, argc, argv, env);
		free(env);
	}
	return (0);
}
