/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:35:27 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 12:36:37 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_for_export(t_env *data)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(data->var, "=\"");
	str2 = ft_strjoin(str1, data->val);
	free(str1);
	str1 = ft_strjoin(str2, "\"");
	free(str2);
	return (str1);
}
