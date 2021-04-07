/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:24:06 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 11:45:34 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A appeler seulement quand on a un char special
*/
t_list	*apply_spefunc(t_iter *line)
{
	static t_spf	tab = {{'\'', get_quote}, {'"', get_dquote},
		{"<", get_lchev}, {">", get_rchev}, {';', get_semic}, {'|', get_pipe},
		{0, 0}};
	size_t	i;

	i = 0;
	while (tab[i].spe && line->line[line->i] != tab[i].spe)
		i++;
	return (tab[i].f(line));
}
