/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:40:07 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/07 12:40:24 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, t_etype token)
{
	t_token	*new;

	if (!str)
		return (0);
	if (!(new = malloc(sizeof(t_token))))
		return (0);
	new->str = str;
	new->token = token;
	return (new);
}

char	*get_wbetw(size_t start, size_t end, char *line)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = malloc(sizeof(char) * (end - start + 1))))
		return (0);
	while (start < end)
	{
		str[i] = line[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}
