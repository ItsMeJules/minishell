/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:15:53 by jules             #+#    #+#             */
/*   Updated: 2021/04/06 15:25:59 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int id)
{
	if (id == TERM_ENV_NOT_FOUND)
		printf("Environment variable 'TERM' not found !");
}
