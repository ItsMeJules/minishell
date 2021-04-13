/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:26:46 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/13 13:59:51 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tckey(char tc[4], int const_tc)
{
	if (const_tc == LEFT_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 68);
	else if (const_tc == UP_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 65);
	else if (const_tc == DOWN_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 66);
	else if (const_tc == RIGHT_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 67);
	else if (const_tc == BACKSPACE_KEY)
		return (tc[0] == 8 || tc[0] == 127);
	return (0);
}
