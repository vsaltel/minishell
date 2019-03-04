/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:18:53 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 18:09:28 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_exceptions(char **text, char **env)
{
	int		i;
	int		s;
	char	*l;
	char	*r;
	char	*tmp;

	while ((r = ft_strchr(*text, '$')))
	{
		s = 0;
		i = 0;
		while (r[s + 1] && r[s + 1] != '$' && r[s + 1] != '\\')
			s++;
		l = ft_strsub(*text, 0, r - *text);
		while (env[i] && (ft_strncmp(r + 1, env[i], s) || env[i][s] != '='))
			i++;
		tmp = l;
		l = env[i] ? ft_strjoin(l, env[i] + s + 1) : ft_strjoin(l, "");
		free(tmp);
		*text = ft_strjoin(l, r + s + 1);
		free(l);
		if (r[s + 1] == '\\')
			break ;
	}
}

char	*tilde_exceptions(char **e, char **env)
{
	int		i;
	char	*t;

	t = *e;
	i = 0;
	if (t[0] == '~' && (t[1] == '\0' || t[1] == '/'))
	{
		while (env[i] && ft_strncmp(env[i], "HOME=", 5))
			i++;
		return (env[i] ? *e = ft_strjoin(env[i] + 5, t + 1) : NULL);
	}
	else if (t[0] == '~' && t[1] == '-' && (t[2] == '\0' || t[2] == '/'))
	{
		while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7))
			i++;
		return (env[i] ? *e = ft_strjoin(env[i] + 7, t + 2) : NULL);
	}
	else if (t[0] == '~' && t[1] == '+' && (t[2] == '\0' || t[2] == '/'))
	{
		while (env[i] && ft_strncmp(env[i], "PWD=", 4))
			i++;
		return (env[i] ? *e = ft_strjoin(env[i] + 4, t + 2) : NULL);
	}
	return (NULL);
}

void	set_token_env(t_token *token, char **env)
{
	int size;

	size = ft_strlen(token->content + 1);
	if (!tilde_exceptions(&token->content, env) && size > 0)
		dollar_exceptions(&token->content, env);
}
