/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:01:24 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 16:01:43 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
