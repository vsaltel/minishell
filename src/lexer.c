/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:45:16 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/18 15:07:16 by vsaltel          ###   ########.fr       */
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
		char **env, int lastret)
{
	t_token *current;
	char	*tmp;

	tilde_exception(item, env);
	if (ft_strlen(item->content + 1) > 0)
		dollar_exceptions(&(item->content), env, lastret);
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
			env, 0);
	prev1 = ++s1;
	*prev = prev1;
	*s = s1;
	return (1);
}

static int		add_current(t_shell *shell, char **s, const char **prev,
		const char *begin)
{
	t_oplist	c;

	c = searchtokentype(*s);
	if ((c.op != 0 || **s == '"' || **s == '\'') && *prev != *s)
		addtolexer((&shell->lexer),
			create_token(*prev, *s - *prev, TOKEN_NAME),
				shell->env, shell->lastret);
	if (c.op != 0)
	{
		*s += c.size;
		if (c.type != TOKEN_EAT)
			addtolexer((&shell->lexer),
				create_token(c.op, c.size, c.type), shell->env, shell->lastret);
		*prev = *s;
	}
	else if ((begin == *s || *(*(s) - 1) != '\\')
			&& (**s == '"' || **s == '\''))
	{
		if (!quote((&shell->lexer), prev, s, shell->env))
			return (0);
	}
	else
		(*s)++;
	return (1);
}

int				fill_lexer(char *s, t_shell *shell)
{
	const char	*prev;
	const char	*begin;

	shell->lexer.size = 0;
	prev = s;
	begin = s;
	while (s && *s)
	{
		if (*s == '\\')
			s++;
		else
		{
			if (!add_current(shell, &s, &prev, begin))
				return (0);
		}
	}
	if (prev != s)
		addtolexer(&(shell->lexer),
			create_token(prev, s - prev, TOKEN_NAME),
				shell->env, shell->lastret);
	return (1);
}
