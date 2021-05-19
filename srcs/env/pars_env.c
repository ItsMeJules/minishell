/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:25:42 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:33:24 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_elem(char *var, char *val)
{
	t_env	*new;

	if (!var)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->var = var;
	new->val = val;
	return (new);
}

void	del_env_elem(void *elem)
{
	t_env	*data;

	data = (t_env *)elem;
	if (data->var)
		free(data->var);
	if (data->val)
		free(data->val);
	free(elem);
}

char	*get_var_from_str(char *str)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i > 0 && str[i - 1] == '+')
		i--;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	while (j < i)
	{
		var[j] = str[j];
		j++;
	}
	var[j] = 0;
	return (var);
}

char	*get_val_from_str(char *str)
{
	size_t	i;
	size_t	j;
	char	*val;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		i++;
	else
		return (0);
	val = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!val)
		return (0);
	while (str[i])
		val[j++] = str[i++];
	val[j] = 0;
	return (val);
}

t_list	*pars_env(char **envp)
{
	size_t	i;
	t_list	*root;
	t_list	*new;

	i = 0;
	root = NULL;
	while (envp[i])
	{
		new = ft_lstnew(create_env_elem(get_var_from_str(envp[i]),
					get_val_from_str(envp[i])));
		if (!new)
		{
			ft_lstclear(&root, &del_env_elem);
			return (0);
		}
		ft_lstadd_back(&root, new);
		i++;
	}
	return (root);
}
