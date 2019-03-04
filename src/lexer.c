/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:53:52 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 14:39:01 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*sstrncpy(char *dst, const char *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;
	size_t	j;

	s = (char *)src;
	d = dst;
	i = -1;
	j = 0;
	while (s[++i] != '\0' && i < len)
	{
		if (s[i] != '\\' || (i > 0 && s[i - 1] == '\\'))
			d[i - j] = s[i];
		else
			j++;
	}
	while (i - j < len)
		d[i++ - j] = '\0';
	return (d);
}

static t_oplist	searchtokentype(char *s)
{
	size_t			i;
	const t_oplist	not_found = {NULL, 0, TOKEN_NULL};

	i = 0;
	while (g_existing_token[i].op)
	{
		if (ft_strncmp(s, g_existing_token[i].op, g_existing_token[i].size) == 0)
			return (g_existing_token[i]);
		i++;
	}
	return (not_found);
}

static t_token	*create_token(const char *text, size_t text_size, t_token_type type)
{
	t_token *item;

	if (!(item = malloc(sizeof(t_token))))
		exit(1);
	if (!(item->content = malloc(sizeof(char) * (text_size + 1))))
		exit(1);
	item->type = type;
	ft_strncpy(item->content, text, text_size);
	item->content[text_size] = '\0';
	item->size = text_size;
	item->next = NULL;
	return (item);
}

static void		addtolexer(t_lexer *lexer, t_token *item, char **env)
{
	t_token *current;
	char	*tmp;

	set_token_env(item, env);
	tmp = ft_strdup(item->content);
	sstrncpy(item->content, tmp, ft_strlen(tmp));
	item->size = ft_strlen(item->content);
	free(tmp);
	if (!lexer->tokens)
		lexer->tokens = item;
	else
	{
		current = lexer->tokens;
		while (current->next)
			current = current->next;
		current->next = item;
	}
	lexer->size++;
}

static int		quote(t_lexer *lexer, const char **prev, char **s, char **env)
{
	const char	*prev1;
	char		*s1;
	int			i;

	i = 2;
	prev1 = *prev;
	s1 = *s;
	prev1 = s1;
	s1++;
	while (*s1 && (*s1 != *prev1 || i % 2 != 0))
	{
		if (*s1 == '\\')
			i++;
		else
			i = 2;
		s1++;
	}
	if (*s1 == '\0')
		return (0);
	addtolexer(lexer, create_token(prev1 + 1, s1 - prev1 - 1, TOKEN_NAME), env);
	prev1 = ++s1;
	*prev = prev1;
	*s = s1;
	return (1);
}

int				fill_lexer(char *s, t_lexer *lexer, char **env)
{
	t_oplist	current;
	const char	*prev;
	const char	*begin;

	lexer->size = 0;
	prev = s;
	begin = s;
	while (s && *s)
	{
		if (*s == '\\')
			s++;
		else
		{
			current = searchtokentype(s);
			if ((current.op != 0 || *s == '"' || *s == '\'') && prev != s)
				addtolexer(lexer, create_token(prev, s - prev, TOKEN_NAME), env);
			if (current.op != 0)
			{
				s += current.size;
				if (current.type != TOKEN_EAT)
					addtolexer(lexer, create_token(current.op, current.size, current.type), env);
				prev = s;
			}
			else if ((begin == s || *(s - 1) != '\\') &&
					(*s == '"' || *s == '\''))
			{
				if (!quote(lexer, &prev, &s, env))
					return (0);
			}
			else
				s++;
		}
	}
	if (prev != s)
		addtolexer(lexer, create_token(prev, s - prev, TOKEN_NAME), env);
	return (1);
}
