/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:33:18 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/06 11:40:29 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum					e_token_type
{
	TOKEN_SEMI,
	TOKEN_EAT,
	TOKEN_NAME,
	TOKEN_NULL
}								t_token_type;

typedef struct					s_oplist
{
	char			*op;
	size_t			size;
	t_token_type	type;
}								t_oplist;

typedef struct					s_token
{
	char			*content;
	size_t			size;
	t_token_type	type;
	struct s_token	*next;
}								t_token;

typedef struct					s_lexer
{
	t_token			*tokens;
	size_t			size;
}								t_lexer;

int								g_ret;

static const t_oplist			g_existing_token[] =
{
	{";", 1, TOKEN_SEMI},
	{" ", 1, TOKEN_EAT},
	{"\t", 1, TOKEN_EAT},
	{"\n", 1, TOKEN_EAT},
	{"\v", 1, TOKEN_EAT},
	{"\r", 1, TOKEN_EAT},
	{"\f", 1, TOKEN_EAT},
	{NULL, 0, TOKEN_NULL}
};

#endif
