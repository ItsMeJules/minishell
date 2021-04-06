/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:15:53 by jules             #+#    #+#             */
/*   Updated: 2021/04/06 16:05:56 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int id, char *info)
{
	if (id == TERM_ENV_NOT_FOUND)
		printf("Environment variable 'TERM' not found !\n");
	else if (id == TERMCAP_DB_ACCESS)
		printf("Access to termcap database failed...\n");
	else if (id == TERM_TYPE_NOT_DEFINED) 
		printf("Term type '%s' doesn't exist in termcap database.\n", info);
}
