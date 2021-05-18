/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:12:36 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/18 15:59:53 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_declare(t_list *env)
{
	char	**envp;
	t_env	*data;
	size_t	i;

	envp = get_envp(env);
	i = 0;
	ft_sort_string_tab(envp);
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
	while (env)
	{
		data = (t_env *)env->content;
		if (!data->val)
			printf("declare -x %s\n", data->var);
		env = env->next;
	}
	return (0);
}

void	switch_var(t_list **dest, t_list **src, char *var)
{
	t_list	*last_env;
	t_list	*to_switch;

	last_env = *dest;
	to_switch = *src;
	while (last_env->next)
		last_env = last_env->next;
	if (!ft_strcmp(((t_env *)to_switch->content)->var, var))
	{
		*src = to_switch->next;
		last_env->next = to_switch;
		last_env->next->next = 0;
	}
	else
	{
		while (to_switch->next
			&& ft_strcmp(((t_env *)to_switch->next->content)->var, var))
			to_switch = to_switch->next;
		last_env->next = to_switch->next;
		to_switch->next = to_switch->next->next;
		last_env->next->next = 0;
	}
}

void	mod_env2(t_list **env, char *var, char *val)
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
				free(var);
				data->val = val;
				return ;
			}
			elem = elem->next;
		}
	}
	ft_lstadd_back(env, ft_lstnew(create_env_elem(var, val)));
}

void	parse_exp_var(char *declare, char *var, t_list **env, t_list **vars)
{
	if (is_var(*vars, var))
		switch_var(env, vars, var);
	if (is_var(*env, var) && is_joinable(declare))
		concat_var(env, var, get_val_from_str(declare));
	else if (is_declaration(declare))
		mod_env2(env, var, get_val_from_str(declare));
	else if (!is_var(*env, var))
		mod_env2(env, var, 0);
	else
		free(var);
}

int		export(int argc, char **argv, t_list **env, t_list **vars)
{
	int		i;
	char	*var;

	i = 1;
	if (argc == 1)
		return (print_declare(*env));
	while (i < argc)
	{
		var = get_var_from_str(argv[i]);
		if (check_var(var))
			parse_exp_var(argv[i], var, env, vars);
		else
		{
			disp_exp_err(var, "export");
			free(var);
		}
		i++;
	}
	return (0);
}
