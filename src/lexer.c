/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:53:52 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/03 18:41:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sstrncpy(char *dst, const char *src, size_t len)
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

t_oplist	searchTokenType(char *s)
{
	size_t i;
	const t_oplist not_found = {NULL, 0, TOKEN_NULL};

	i = 0;
	while (existing_token[i].op)
	{
			if (ft_strncmp(s, existing_token[i].op, existing_token[i].size) == 0)
				return (existing_token[i]);
		i++;
	}
	return (not_found);
}

void		addToLexer(t_lexer* lexer, const char *text, size_t text_size, e_token_type type)
{
	t_token *item;
	t_token *current;

	if (!(item = malloc(sizeof(t_token))))
		exit(1);
	if (!(item->content = malloc(sizeof(char) * (text_size + 1))))
		exit(1);
	item->type = type;
	sstrncpy(item->content, text, text_size);
	item->content[text_size] = '\0';
	item->size = text_size;
	item->next = NULL;
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

int			quote(t_lexer *lexer, const char **prev, char **s)
{
	const char *prev1;
	char *s1;
	int i;

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
	addToLexer(lexer, prev1 + 1, s1 - prev1 - 1, TOKEN_NAME);
	prev1 = ++s1;
	*prev = prev1;
	*s = s1;
	return (1);
}

int			fill_lexer(char *s, t_lexer *lexer)
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
			current = searchTokenType(s);
			if ((current.op != 0 || *s == '"' || *s == '\'') && prev != s)
				addToLexer(lexer, prev, s - prev, TOKEN_NAME);
			if (current.op != 0)
			{
				s += current.size;
				if (current.type != TOKEN_EAT)
					addToLexer(lexer, current.op, current.size, current.type);
				prev = s;
			}
			else if ((begin == s || *(s - 1) != '\\') && (*s == '"' || *s == '\''))
			{
				if (!quote(lexer, &prev, &s))
					return (0);
			}
			else
				s++;
		}
	}
	if (prev != s)
		addToLexer(lexer, prev, s - prev, TOKEN_NAME);
	return (1);
}
