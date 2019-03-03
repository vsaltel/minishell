/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:20:13 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/26 19:21:59 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	nbword(char const *s, char c)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	if (s[0] != c && s[0] != '\0')
		k++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			k++;
		i++;
	}
	return (k);
}

static	void	cutting(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (s[i] != '\0')
		{
			tab[k] = ft_strsub(s, i, (j - i));
			k++;
		}
		i = j;
	}
	tab[k] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(*tab) * (nbword(s, c) + 1))))
		return (NULL);
	cutting(tab, s, c);
	return (tab);
}
