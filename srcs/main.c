/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/05/21 13:46:07 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_shell(int argc, char **envp)
{
	if (argc != 1)
	{
		disp_error(ARG_ERR);
		return (false);
	}
	g_tc.env = pars_env(envp);
	if (!g_tc.env)
	{
		disp_error(ENV_ERR);
		return (false);
	}
	else if (!isatty(0))
		return (false);
	else if (init_termcap() < 0)
		return (false);
	g_tc.signal = 0;
	return (true);
}

void	init_setup(t_setup *setup)
{
	char	*shlvl;

	if (!is_var(g_tc.env, "PWD"))
		mod_env(&g_tc.env, "PWD", getcwd(setup->path, 4096));
	else if (!is_var(g_tc.env, "SHLVL"))
		mod_env(&g_tc.env, "SHLVL", "1");
	else
	{
		shlvl = ft_itoa(ft_atoi(get_env_val(g_tc.env, "SHLVL")) + 1);
		mod_env(&g_tc.env, "SHLVL", shlvl);
		free(shlvl);
	}
	setup->vars = NULL;
	mod_env(&setup->vars, "?", "0");
	setup->history = read_file(FILE_HISTORY_NAME);
}

bool	lexing(t_setup *setup)
{
	save_command(setup->iter->line, setup->history);
	setup->lexer = NULL;
	setup->lexer = tokenize_input(setup->iter);
	if (setup->iter->err)
	{
		lexer_free(&setup->lexer, setup->iter);
		return (false);
	}
	if (!check_parsing(setup->lexer))
	{
		lexer_free(&setup->lexer, setup->iter);
		disp_error(PARS_ERR);
		mod_env(&setup->vars, "?", "2");
		return (false);
	}
	return (true);
}

void	launch_shell(t_setup *setup)
{
	char	path[4096];

	while (42)
	{
		print_prompt(getcwd(path, 4096));
		get_cursor_pos();
		setup->iter = readu_input(setup);
		change_term_mode(0);
		g_tc.cursor_pos = 0;
		if (!lexing(setup) || setup->iter->err)
		{
			change_term_mode(1);
			continue ;
		}
		rm_unused_spaces(&setup->lexer);
		if (setup->lexer)
		{
			setup->ast = parse_ast(setup->lexer);
			exec(setup->ast, setup, &exec_fork);
			btree_clear(setup->ast, free_ast_item);
		}
		change_term_mode(1);
		free(setup->iter->line);
		free(setup->iter);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_setup	setup;

	(void)argv;
	if (!init_shell(argc, envp))
		return (1);
	init_setup(&setup);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	launch_shell(&setup);
	ft_lstclear(&g_tc.env, &del_env_elem);
	ft_lstclear(&setup.vars, &del_env_elem);
	free_history(setup.history);
	return (0);
}
