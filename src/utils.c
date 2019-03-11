/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:35:32 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/08 17:01:32 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_env_variable(char *cmp, int lenght, char **env)
{
	int i;

	if (!env || !cmp)
		return (NULL);
	i = 0;
	while (env[i] && (ft_strncmp(cmp, env[i], lenght) || env[i][lenght] != '='))
		i++;
	if (env[i])
		return (env[i]);
	else
		return (NULL);
}

char			**create_env_variable(char *name, char *value, char **env)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = copy_env(env, 1);
	i = 0;
	while (tab[i])
		i++;
	tab[i] = ft_strjoin(name, "=");
	if (value)
	{
		tmp = tab[i];
		tab[i] = ft_strjoin(tmp, value);
		free(tmp);
	}
	tab[i + 1] = NULL;
	return (tab);
}

char			**delete_env_variable(char *name, char **env)
{
	char	**tab;
	int		i;
	int		k;

	i = 0;
	while (env[i])
		i++;
	if (!(tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], name, ft_strlen(name)) == 0 &&
			env[i][ft_strlen(name)] == '='))
			tab[k++] = ft_strdup(env[i]);
		i++;
	}
	tab[k] = NULL;
	free_tab(env);
	return (tab);
}

static size_t	strl_pathfile(const char *s1, const char *s2)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i])
		i++;
	if (s1[i - 1] != '/')
		i++;
	while (s2[y])
		y++;
	y++;
	return (i + y);
}

char			*str_pathfile(const char *s1, const char *s2)
{
	size_t	i;
	char	*dst;

	if (!(dst = malloc(sizeof(char) * strl_pathfile(s1, s2))))
		exit(1);
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1)
		dst[i++] = *s1++;
	if (dst[i - 1] != '/')
		dst[i++] = '/';
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
