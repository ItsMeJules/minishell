/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:09:12 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:23:02 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	get_env_size(t_list *env)
{
	t_env	*data;
	int		i;

	i = 0;
	while (env)
	{
		data = (t_env *)env->content;
		if (data->val)
			i++;
		env = env->next;
	}
	return (i);
}

char	**get_envp(t_list *env)
{
	char	**envp;
	t_env	*data;
	char	*tmp;
	size_t	i;

	envp = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!envp)
		return (0);
	i = 0;
	while (env)
	{
		data = (t_env *)env->content;
		if (data->val)
		{
			tmp = ft_strjoin(data->var, "=");
			envp[i] = ft_strjoin(tmp, data->val);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	envp[i] = 0;
	return (envp);
}

char	*get_env_val(t_list *env, char *var)
{
	t_env	*data;

	while (env)
	{
		data = (t_env *)env->content;
		if (!ft_strcmp(var, data->var))
			return (data->val);
		env = env->next;
	}
	return ("");
}

void	mod_env(t_list **env, char *var, char *val)
{
	t_list	*elem;
	t_env	*data;

	if (*env)
	{
		elem = *env;
		while (elem)
		{
			data = (t_env *)elem->content;
			if (!ft_strcmp(var, data->var))
			{
				free(data->val);
				if (!val)
					data->val = ft_strdup("");
				else
					data->val = ft_strdup(val);
				return ;
			}
			elem = elem->next;
		}
	}
	var = ft_strdup(var);
	val = ft_strdup(val);
	ft_lstadd_back(env, ft_lstnew(create_env_elem(var, val)));
}
