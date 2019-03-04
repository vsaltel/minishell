/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:35:32 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 13:23:09 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				true_variable(char *env, char *arg)
{
	int j;

	j = 0;
	while (arg[j])
		j++;
	if (ft_strncmp(env, arg, ft_strlen(arg)) == 0 && env[j] == '=')
		return (1);
	return (0);
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
