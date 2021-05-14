/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/05/14 19:45:34 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_shell(int argc, char **envp, t_setup *setup)
{
	if (argc != 1)
	{
		disp_error(ARG_ERR);
		return (false);
	}
	setup->env = pars_env(envp);
	if (!setup->env)
	{
		disp_error(ENV_ERR);
		return (false);
	}
	else if (!isatty(0))
		return (false);
	else if (init_termcap() < 0)
		return (false);
	return (true);
}

void	init_setup(t_setup *setup)
{
	char	*shlvl;

	if (!is_var(setup->env, "PWD"))
		mod_env(&setup->env, "PWD", getcwd(setup->path, 4096));
	else if (!is_var(setup->env, "SHLVL"))
		mod_env(&setup->env, "SHLVL", "1");
	else
	{
		shlvl = ft_itoa(ft_atoi(get_env_val(setup->env, "SHLVL")) + 1);
		mod_env(&setup->env, "SHLVL", shlvl);
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
	if (!check_parsing(setup->lexer))
	{
		disp_error(PARS_ERR);
		lexer_free(setup->lexer, setup->iter);
		mod_env(&setup->vars, "?", "258");
		return (false);
	}
	return (true);
}

void	launch_shell(t_setup *setup)
{
	while (42)
	{
		print_prompt(get_env_val(setup->env, "PWD"));
		get_cursor_pos();
		setup->iter = readu_input(setup->history);
		change_term_mode(0);
		if (setup->iter->err)
			lexer_free(setup->lexer, setup->iter);
		g_tc.cursor_pos = 0;
		if (!setup->iter->line || !lexing(setup))
		{
			change_term_mode(1);
			free(setup->iter->line);
			free(setup->iter);
			continue ;
		}
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
	if (!init_shell(argc, envp, &setup))
		return (1);
	init_setup(&setup);
	launch_shell(&setup);
	ft_lstclear(&setup.env, &del_env_elem);
	ft_lstclear(&setup.vars, &del_env_elem);
	free_history(setup.history);
	return (0);
}
