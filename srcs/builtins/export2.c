/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:37 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:21:35 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_envp2(t_list *env)
{
	char	**envp;
	t_env	*data;
	size_t	i;

	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!envp)
		return (0);
	i = 0;
	while (env)
	{
		data = (t_env *)env->content;
		if (data->val)
			envp[i] = join_for_export(data);
		else
			envp[i] = ft_strdup(data->var);
		i++;
		env = env->next;
	}
	envp[i] = 0;
	return (envp);
}

bool	is_declaration(char *str)
{
	size_t	i;
	char	*var;

	i = 0;
	if (!ft_strchr(str, '=') || ft_isdigit(str[0]))
		return (false);
	while (str[i] != '=')
		i++;
	if (!i)
		return (false);
	if (str[i - 1] == 92)
		return (false);
	var = get_var_from_str(str);
	if (!check_var(var))
	{
		free(var);
		return (false);
	}
	free(var);
	return (true);
}

bool	is_joinable(char *str)
{
	char	*ptr;

	ptr = ft_strchr(str, '=');
	if (!ptr)
		return (false);
	ptr--;
	if (*ptr == '+')
		return (true);
	return (false);
}

bool	check_var(char *str)
{
	size_t	i;

	i = 1;
	if (!str || !ft_strlen(str))
		return (false);
	else if (ft_isdigit(str[0]) || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	while (str[i])
	{
		if (!ft_isalpha(str[0]) && str[0] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	concat_var(t_list **env, char *var, char *val)
{
	char	*new;

	new = ft_strjoin(get_env_val(*env, var), val);
	mod_env2(env, var, new);
	free(val);
}
