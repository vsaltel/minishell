/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:18:53 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/13 18:44:57 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_slash(int nb, char *str)
{
	char	*s;
	int		i;
	int		j;

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
	return (s);
}

static char	*strdup_slash(char *str)
{
	int		i;
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
		s = fill_slash(nb, str);
	else
		return (ft_strdup(str));
	return (s);
}

static int	majl(char **l, char *r, char **env, int lastret)
{
	char	*tmp;
	char	*tmp2;
	int		s;

	s = 0;
	while (r[s + 1] && r[s + 1] != '$' && r[s + 1] != '\\' && r[s] != '?')
		s++;
	tmp2 = *l;
	tmp = *(r + 1) == '?' ? ft_itoa(lastret) :
		strdup_slash(get_env_variable(r + 1, s, env));
	if (*(r + 1) == '?')
		*l = ft_strjoin(*l, tmp);
	else
		*l = tmp ? ft_strjoin(*l, tmp + s + 1) : ft_strjoin(*l, "");
	free(tmp2);
	free(tmp);
	return (s);
}

static void	dollar_exceptions(char **text, char **env, int lastret)
{
	int		s;
	char	*l;
	char	*r;

	l = NULL;
	r = *text - 1;
	while ((r = sstrchr(++r, '$')))
	{
		if (!l)
			l = ft_strsub(*text, 0, r - *text);
		s = majl(&l, r, env, lastret);
		r = &r[s];
		s = 0;
		while (r[s + 1] == '\\')
			s = s + 2;
		while (r[s + 1] && r[s + 1] != '$' && r[s] != '?')
			s++;
		if (s > 0)
			l = ft_strfjoin(l, ft_strsub(r, 2, s - 1), l);
	}
	if (l)
	{
		free(*text);
		*text = l;
	}
}

void		set_token_env(t_token *token, char **env, int lastret)
{
	int		i;
	char	*t;
	char	*ret;

	t = token->content;
	i = 0;
	if (t[0] == '~' && (t[1] == '\0' || t[1] == '/' || t[1] == '$'))
	{
		if ((ret = get_env_variable("HOME", 4, env)))
			token->content = ft_strfjoin(ret + 5, t + 1, token->content);
	}
	else if (t[0] == '~' && t[1] == '-' && (t[2] == '\0' ||
				t[2] == '/' || t[2] == '$'))
	{
		if ((ret = get_env_variable("OLDPWD", 6, env)))
			token->content = ft_strfjoin(ret + 7, t + 2, token->content);
	}
	else if (t[0] == '~' && t[1] == '+' && (t[2] == '\0' ||
				t[2] == '/' || t[2] == '$'))
	{
		if ((ret = get_env_variable("PWD", 3, env)))
			token->content = ft_strfjoin(ret + 4, t + 2, token->content);
	}
	if (ft_strlen(token->content + 1) > 0)
		dollar_exceptions(&token->content, env, lastret);
}
