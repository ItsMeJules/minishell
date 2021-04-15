/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/15 13:40:14 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	*readu_input(t_history *history)
{
	t_iter	*iter;

	if (!(iter = malloc(sizeof(t_iter))))
	{
		return (NULL);
	}
	iter->i = 0;
	iter->err = NULL;
	iter->line = NULL;
	read_bpb(&iter->line, history);
	return (iter);
}

void	print_prompt()
{
	write(1, "minishit> ", 10);
}

void	disp_lexer(t_list *root);

int	main(int argc, char **argv, char **envp)
{
	t_iter		*iter;
	t_list		*list;
	t_list		*env;
	t_termcap	tc;
	t_history	*history;

	(void)argc;
	(void)argv;
	init_termcap(&tc);
	history = read_file(FILE_HISTORY_NAME);
	while (42)
	{
		print_prompt();
		get_cursor_pos();
		iter = readu_input(history);
		save_command(iter->line, history);
		list = NULL;
		list = tokenize_input(iter);
		if (list)
			disp_lexer(list);
		lexer_free(list, iter);
		if (!(env = pars_env(envp)))
			printf("ENV ERROR\n");
		ft_lstclear(&env, &del_env_elem);
	}
	change_term_mode(&tc, 0);
	return (0);
}
