/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:18:53 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/03 18:41:07 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_exceptions(char **text, char **env)
{
	int i;
	int size;
	char *left;
	char *right;
	char *tmp;

	while ((right = ft_strchr(*text, '$')))
	{
		size = 0;
		i = 0;
		while (right[size + 1] && right[size + 1] != '$' && right[size + 1] != '\\')
			size++;
		left = ft_strsub(*text, 0, right - *text);
		while (env[i] && (ft_strncmp(right + 1, env[i], size) || env[i][size] != '='))
			i++;
		tmp = left;
		left = env[i] ? ft_strjoin(left, env[i] + size + 1) : ft_strjoin(left, "");
		free(tmp);
		*text = ft_strjoin(left, right + size + 1);
		free(left);
	}
}

char	*tilde_exceptions(char **e, char **env)
{
	int i;
	char *text;

	text = *e;
	i = 0;
	if (text[0] == '~' && (text[1] == '\0' || text[1] == '/'))
	{
		while (env[i] && ft_strncmp(env[i], "HOME=", 5))
			i++;
		return (*e = ft_strjoin(env[i] + 5, text + 1));
	}
	else if (text[0] == '~' && text[1] == '-' && (text[2] == '\0' || text[2] == '/'))
	{
		while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7))
			i++;
		return (*e = ft_strjoin(env[i] + 7, text + 2));
	}
	else if (text[0] == '~' && text[1] == '+' && (text[2] == '\0' || text[2] == '/'))
	{
		while (env[i] && ft_strncmp(env[i], "PWD=", 4))
			i++;
		return (*e = ft_strjoin(env[i] + 4, text + 2));
	}
	return (NULL);
}

void	set_lexer_env(t_lexer *lexer, char **env)
{
	t_token	*begin;
	char *tmp;
	int i;
	int size;

	begin = lexer->tokens;
	while (lexer->tokens)
	{
		tmp = lexer->tokens->content;
		size = ft_strlen(lexer->tokens->content + 1);
		if (!tilde_exceptions(&lexer->tokens->content, env) && size > 0)
			dollar_exceptions(&lexer->tokens->content, env);
		if (ft_strcmp(tmp, lexer->tokens->content))
			free(tmp);
		lexer->tokens = lexer->tokens->next;
	}
	lexer->tokens = begin;
}
/*
void	set_text_env(char *text, char **env)
{
	t_token	*begin;
	char *tmp;
	int i;
	int size;

	size = ft_strlen(text + 1);
	if (!tilde_exceptions(&text, env) && size > 0)
		dollar_exceptions(&text, env);
}
*/
