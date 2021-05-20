/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:01:24 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/20 15:54:39 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dot_only_err(t_setup *setup, t_exec *ex)
{
	ft_putstr_fd(TERM_NAME, 2);
	ft_putstr_fd(": .: filename argument required\n", 2);
	mod_env(&setup->vars, "?", "2");
	reset_ex(ex);
}

int	disp_fd_error(char *filename, char *err)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, ": ", 2);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	return (0);
}
