/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:27:05 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/20 15:13:53 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_err(char *str)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": unset: `", 10);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
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

void	disp_exp_err(char *var, char *fct)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": ", 2);
	write(2, fct, ft_strlen(fct));
	write(2, ": `", 3);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier\n", 26);
}

int	unset(int argc, char **argv, t_list **env, t_list **vars)
{
	int		i;
	int		ret;
	char	*var;

	i = 1;
	ret = 0;
	while (i < argc)
	{
		var = get_var_from_str(argv[i]);
		if (!check_var(var))
			disp_exp_err(var, "unset");
		else if (is_declaration(argv[i]))
			ret = unset_err(argv[i]);
		else if (is_var(*env, argv[i]))
			remove_var(env, argv[i]);
		else if (is_var(*vars, argv[i]))
			remove_var(vars, argv[i]);
		free(var);
		i++;
	}
	return (ret);
}
