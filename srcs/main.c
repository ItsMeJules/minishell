/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/05/11 16:32:13 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	*readu_input(t_history *history)
{
	t_iter	*iter;

	if (!(iter = malloc(sizeof(t_iter))))
		return (NULL);
	iter->i = 0;
	iter->err = NULL;
	iter->line = NULL;
	read_bpb(&iter->line, history);
	history->pos = -1;
	ft_putstr_fd(NORMAL, 1);
	return (iter);
}

void	print_prompt(char *path)
{
	char	*curr_dir;

	ft_putstr_fd(CYAN, 1);
	ft_putstr_fd("minishit ", 1);
	ft_putstr_fd(BOLD, 1);
	ft_putstr_fd(WHITE, 1);
	ft_putstr_fd("$", 1);
	ft_putstr_fd(LIGHT_CYAN, 1);
	curr_dir = ft_strrchr(path, '/');
	if (curr_dir)
		ft_putstr_fd(curr_dir + 1, 1);
	else
		ft_putstr_fd(path, 1);
	ft_putstr_fd(DARK_GRAY, 1);
	ft_putstr_fd("> ", 1);
	ft_putstr_fd(DEFAULT_COLOR, 1);
}

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
	if (!is_var(setup->env, "PWD"))
		mod_env(&setup->env, "PWD", getcwd(setup->path, 4096));
	else if (!is_var(setup->env, "SHLVL"))
		mod_env(&setup->env, "SHLVL", "1");
	else
		mod_env(&setup->env, "SHLVL"
			, ft_itoa(ft_atoi(get_env_val(setup->env, "SHLVL")) + 1));
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
			continue ;
		if (setup->lexer)
		{
			setup->ast = parse_ast(setup->lexer);
			exec(setup->ast, &setup->env, &setup->vars);
			btree_clear(setup->ast, free_ast_item);
		}
		change_term_mode(1);
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
/*
	while (42)
	{
		print_prompt(get_env_val(env, "PWD"));
		get_cursor_pos();
		iter = readu_input(history);
		change_term_mode(0);
		if (iter->err)
			lexer_free(lexer, iter);
		g_tc.cursor_pos = 0;
		if (iter->line == NULL)
			continue ;
		save_command(iter->line, history);
		lexer = NULL;
		lexer = tokenize_input(iter);
		if (!check_parsing(lexer))
		{
			disp_error(PARS_ERR);
			lexer_free(lexer, iter);
			mod_env(&vars, "?", "258");
			continue ;
		}
		if (ft_strcmp(iter->line, "exit") == 0)
		{
			lexer_free(lexer, iter);
			break ;
		}

		if (lexer)
		{
			ast = parse_ast(lexer);
			exec(ast, &env, &vars);
			btree_clear(ast, free_ast_item);
		}
	}*/
}
