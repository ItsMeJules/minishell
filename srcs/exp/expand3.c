/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:26:52 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/15 18:24:44 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dsign(char *str, t_list *env, t_list *vars)
{
	char	*ret;

	if (ft_strlen(str) == 1)
		return (str);
	else if (is_env(env, str + 1))
		ret = ft_strdup(get_env_val(env, str + 1));
	else
		ret = ft_strdup(get_env_val(vars, str + 1));
	free(str);
	return (ret);
}

char	*expand_bslash(char *str, t_etype type)
{
	char	*ret;

	if (ft_strlen(str) == 1)
	{
		if (type == D_QUOTE)
			return (str);
		ret = ft_strdup("");
		free(str);
		return (ret);
	}
	ret = ft_strdup(str + 1);
	free(str);
	return (ret);
}

char	*join_split(t_list *split)
{
	char	*ret;
	char	*temp;

	ret = 0;	
	while (split)
	{
		if (!ret)
			ret = ft_strdup((char *)split->content);
		else
		{
			temp = ret;
			ret = ft_strjoin(temp, (char *)split->content);
			free(temp);
		}
		split = split->next;
	}
	return (ret);
}
