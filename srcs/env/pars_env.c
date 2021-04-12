/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:25:42 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/12 17:59:02 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_elem(char *var, char *val)
{
	t_env	*new;

	if (!var || !val || !(new = malloc(sizeof(t_env))))
		return (0);
	new->var = var;
	new->val = val;
	return (new);
}

void	del_env_elem(void *elem)
{
	t_env	*data;

	data = (t_env *)elem;
	free(data->var);
	free(data->val);
	free(elem);
}

char	*get_var_from_str(char *str)
{
	size_t	i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!(var = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = 0;
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
	if (!(val = malloc(sizeof(char) * (ft_strlen(str) - i + 1))))
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
	t_env	*env;

	i =	0;
	root = 0;
	while (envp[i])
	{
		if (!(env = create_env_elem(get_var_from_str(envp[i])
			, get_val_from_str(envp[i]))))
		{
			ft_lstclear(&root, &del_env_elem);
			return (0);
		}
		if (!(new = ft_lstnew(env)))
		{
			ft_lstclear(&root, &del_env_elem);
			return (0);
		}
		ft_lstadd_back(&root, new);
		i++;
	}
	return (root);
}
