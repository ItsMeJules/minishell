/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:52:11 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 15:34:34 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

short	is_charset(char c, char *charset)
{
	unsigned int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	get_word_size(char *str, char *charset)
{
	unsigned int	i;

	i = 0;
	while (str[i] && is_charset(str[i], charset) == false)
		i++;
	return (i + 1);
}

void	fill_tab(char **tab, char *str, char *charset, unsigned int count)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	while (i < count)
	{
		k = 0;
		while (str[j] && is_charset(str[j], charset) == true)
			j++;
		tab[i] = malloc(sizeof(char) * get_word_size(str + j, charset));
		if (!tab[i])
			return ;
		while (str[j] && is_charset(str[j], charset) == false)
		{
			tab[i][k] = str[j];
			k++;
			j++;
		}
		tab[i][k] = 0;
		i++;
	}
	tab[i] = 0;
}

char	**ft_split(char *str, char *charset)
{
	char			**tab;
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (!str || !charset)
	{
		tab = malloc(sizeof(char *));
		tab[0] = 0;
		return (tab);
	}
	while (str[i])
	{
		while ((is_charset(str[i], charset) == true && str[i]))
			i++;
		if (str[i])
			count++;
		while (is_charset(str[i], charset) == false && str[i])
			i++;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	fill_tab(tab, str, charset, count);
	return (tab);
}
