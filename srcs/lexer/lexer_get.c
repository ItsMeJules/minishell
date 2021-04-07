/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:48:37 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/07 12:39:28 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_list	*get_quote(t_iter *iter)
{
	size_t	i;
	t_token	*token;

	i = iter->i + 1;
	while (iter->line[i] && iter->line[i] != ''' && iter->line[i - 1] != '\\')
		i++;
	if (!iter->line[i])
	{
		iter->err = 10;
		return (0);
	}
	else if (!create_token(get_wbetw(iter->i + 1, i, iter->line), QUOTE))
	{
		iter->err == 1;
		return 0;
	}
	
}
