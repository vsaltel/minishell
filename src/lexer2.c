/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:14:35 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/14 19:00:11 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*create_token(const char *text, size_t text_size,
		t_token_type type)
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

char		*sstrncpy(char *dst, const char *src, size_t len)
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
