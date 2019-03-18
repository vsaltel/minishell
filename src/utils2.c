/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:47:09 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/18 12:41:29 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			display_env(char **env, int *ret)
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

char			*sstrchr(const char *s, int c)
{
	char	*src;

	src = (char *)s;
	while (*src)
	{
		if (*src == (char)c && (src == s || *(src - 1) != '\\'))
			return (src);
		src++;
	}
	if (*src == (char)c)
		return (src);
	return (NULL);
}

char			*ft_strfjoin(char const *s1, char const *s2, char const *f)
{
	char	*dst;

	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	free((char *)f);
	return (dst);
}

char			*ft_strfdup(const char *s1, const char *f)
{
	char	*dest;

	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	ft_strcpy(dest, s1);
	free((char *)f);
	return (dest);
}

int				is_dir(int *ret, char *str, char *display)
{
	struct stat	fstat;

	if (stat(str, &fstat) == -1)
		return (2);
	if (S_ISDIR(fstat.st_mode))
		return ((*ret = error_exec(2, "minishell", display, 1)));
	return (0);
}
