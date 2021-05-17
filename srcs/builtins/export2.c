/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:37 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/17 14:26:38 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_declaration(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(str, '=') || ft_isdigit(str[0]))
		return (false);
	while (str[i] != '=')
		i++;
	if (!i)
		return (false);
	if (str[i - 1] == 92)
		return (false);
	return (true);
}

bool	is_joinable(char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
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

bool	check_env_args(int argc, char **argv, char *fct)
{
	int		i;
	char	*var;
	bool	ok;

	i = 1;
	ok = true;
	while (i < argc)
	{
		var = get_var_from_str(argv[i]);
		if (!check_var(var))
		{
			write(2, TERM_NAME, ft_strlen(TERM_NAME));
			write(2, ": ", 2);
			write(2, fct, ft_strlen(fct));
			write(2, ": `", 3);
			write(2, var, ft_strlen(var));
			write(2, "': not a valid identifier\n", 26);
			ok = false;
		}
		free(var);
		i++;
	}
	return (ok);
}
