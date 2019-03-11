/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:53:52 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/11 12:16:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_oplist	searchtokentype(char *s)
{
	size_t			i;
	const t_oplist	not_found = {NULL, 0, TOKEN_NULL};

	i = 0;
	while (g_existing_token[i].op)
	{
		if (ft_strncmp(s, g_existing_token[i].op,
				g_existing_token[i].size) == 0)
			return (g_existing_token[i]);
		i++;
	}
	return (not_found);
}

static void		addtolexer(t_lexer *lexer, t_token *item,
		char **env)
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
	addtolexer(lexer, create_token(prev1 + 1, s1 - prev1 - 1, TOKEN_NAME),
			env);
	prev1 = ++s1;
	*prev = prev1;
	*s = s1;
	return (1);
}

static int		add_current(char **s, const char **prev, t_lexer *l, char **env)
{
	t_oplist	c;

	c = searchtokentype(*s);
	if ((c.op != 0 || **s == '"' || **s == '\'') && *prev != *s)
		addtolexer(l, create_token(*prev, *s - *prev, TOKEN_NAME), env);
	if (c.op != 0)
	{
		*s += c.size;
		if (c.type != TOKEN_EAT)
			addtolexer(l, create_token(c.op, c.size, c.type), env);
		*prev = *s;
		return (1);
	}
	return (0);
}

int				fill_lexer(char *s, t_lexer *l, char **env)
{
	const char	*prev;
	const char	*begin;

	l->size = 0;
	prev = s;
	begin = s;
	while (s && *s)
	{
		if (*s == '\\')
			s++;
		else
		{
			if (!add_current(&s, &prev, l, env) &&
				(begin == s || *(s - 1) != '\\') && (*s == '"' || *s == '\''))
			{
				if (!quote(l, &prev, &s, env))
					return (0);
			}
			else
				s++;
		}
	}
	if (prev != s)
		addtolexer(l, create_token(prev, s - prev, TOKEN_NAME), env);
	return (1);
}
