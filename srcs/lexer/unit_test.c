/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:19:51 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/07 16:11:17 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disp_lexer(t_list *root)
{
	t_token	*data;

	while (root)
	{
		data = (t_token *)root->content;
		if (data->token == QUOTE)
			printf("TYPE : QUOTE --- ");
		else if (data->token == D_QUOTE)
			printf("TYPE : D_QUOTE --- ");
		else if (data->token == PIPE)
			printf("TYPE : PIPE --- ");
		else if (data->token == CHEV_R)
			printf("TYPE : CHEV_R --- ");
		else if (data->token == CHEV_L)
			printf("TYPE : CHEV_L --- ");
		else if (data->token == D_CHEV_R)
			printf("TYPE :  D_CHEV_R --- ");
		else if (data->token == SEMI)
			printf("TYPE :  SEMI --- ");
		else
			printf("TYPE :  BASE --- ");
		printf("STR : %s\n", data->str);
		root = root->next;
	}
}
