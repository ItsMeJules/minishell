/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:09:12 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/14 19:13:32 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disp_env(t_list *env)
{
	t_env	*data;

	while (env)
	{
		data = (t_env *)env->content;
		printf("%s=%s\n", data->var, data->val);
		env = env->next;
	}
}

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

char	**get_envp(t_list *env)
{
	char	**envp;
	t_env	*data;
	char	*tmp;
	size_t	i;

	if (!(envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1))))
		return (0);
	i = 0;
	while (env)
	{
		data = (t_env *)env->content;
		tmp = ft_strjoin(data->var, "=");
		envp[i] = ft_strjoin(tmp, data->val);
		free(tmp);
		i++;
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
