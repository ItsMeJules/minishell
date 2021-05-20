/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:40:07 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/20 15:36:42 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, t_etype token)
{
	t_token	*new;

	if (!str)
		return (0);
	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->str = str;
	new->token = token;
	new->rm = false;
	return (new);
}

char	*get_wbetw(size_t start, size_t end, char *line)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
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

int	count_backslash(char *start)
{
	size_t	i;
	int		count;

	i = -1;
	count = 0;
	while (start[++i] == 92)
		count++;
	return (count);
}

void	lexer_free(t_list **root, t_iter *iter)
{
	if (iter->err)
		write(2, iter->err, ft_strlen(iter->err));
	ft_lstclear(root, free_token);
	free(iter->line);
	free(iter);
}
