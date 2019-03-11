/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:18:53 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/08 18:03:07 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*sstrchr(const char *s, int c)
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

static char	*strdup_slash(char *str)
{
	int		i;
	int		j;
	int		nb;
	char	*s;

	if (!str)
		return (NULL);
	i = -1;
	nb = 0;
	while (str[++i])
		if (str[i] == '\\')
			nb++;
	if (nb)
	{
		if (!(s = malloc(sizeof(char) * (ft_strlen(str) + nb + 1))))
			return (NULL);
		i = -1;
		j = 0;
		while (str[++i])
		{
			s[j++] = str[i];
			if (str[i] == '\\')
				s[j++] = str[i];
		}
		s[j] = '\0';
	}
	else
		return (ft_strdup(str));
	return (s);
}

static void	dollar_exceptions(char **text, char **env)
{
	int		s;
	char	*l;
	char	*r;
	char	*tmp;
	char	*tmp2;

	while ((r = sstrchr(*text, '$')))
	{
		s = 0;
		while (r[s + 1] && r[s + 1] != '$' && r[s + 1] != '\\')
			s++;
		l = ft_strsub(*text, 0, r - *text);
		tmp = l;
		tmp2 = strdup_slash(get_env_variable(r + 1, s, env));
		l = tmp2 ? ft_strjoin(l, tmp2 + s + 1) : ft_strjoin(l, "");
		free(tmp);
		free(tmp2);
		*text = ft_strjoin(l, r + s + 1);
		free(l);
	}
}

static char	*tilde_exceptions(char **e, char **env)
{
	int		i;
	char	*t;
	char	*ret;

	t = *e;
	i = 0;
	if (t[0] == '~' && (t[1] == '\0' || t[1] == '/'))
		return ((ret = get_env_variable("HOME", 4, env)) ?
				*e = ft_strjoin(ret + 5, t + 1) : NULL);
	else if (t[0] == '~' && t[1] == '-' && (t[2] == '\0' || t[2] == '/'))
		return ((ret = get_env_variable("OLDPWD", 6, env)) ?
				*e = ft_strjoin(ret + 7, t + 2) : NULL);
	else if (t[0] == '~' && t[1] == '+' && (t[2] == '\0' || t[2] == '/'))
	{
		return ((ret = get_env_variable("PWD", 3, env)) ?
				*e = ft_strjoin(ret + 4, t + 2) : NULL);
	}
	return (NULL);
}

void		set_token_env(t_token *token, char **env)
{
	int size;

	size = ft_strlen(token->content + 1);
	if (!tilde_exceptions(&token->content, env) && size > 0)
		dollar_exceptions(&token->content, env);
}
