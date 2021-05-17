/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:12:36 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/17 15:50:09 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_declare(t_list *env)
{
	char	**envp;
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

void	remove_var(t_list **vars, char *var)
{
	t_list	*elem;
	t_list	*tmp;

	elem = *vars;
	if (!ft_strcmp(((t_env *)elem->content)->var, var))
	{
		*vars = elem->next;
		ft_lstdelone(elem, &del_env_elem);
	}
	else
	{
		while (elem->next
			&& ft_strcmp(((t_env *)elem->next->content)->var, var))
			elem = elem->next;
		tmp = elem->next;
		elem->next = elem->next->next;
		ft_lstdelone(tmp, &del_env_elem);
	}
}

int		export(int argc, char **argv, t_list **env, t_list **vars)
{
	int		i;
	char	*var;

	i = 1;
	if (argc == 1)
		return (print_declare(*env));
	else if (!check_env_args(argc, argv, "export"))
		return (1);
	while (i < argc)
	{
		var = get_var_from_str(argv[i]);
		if (is_var(*vars, var))
			switch_var(env, vars, var);
		if (is_var(*env, var) && is_joinable(argv[i]))
			concat_var(env, var, get_val_from_str(argv[i]));
		else if (is_declaration(argv[i]))
			mod_env2(env, var, get_val_from_str(argv[i]));
		else if (!is_var(*env, var))
			mod_env2(env, var, 0);
		else
			free(var);
		i++;
	}
	return (0);
}
