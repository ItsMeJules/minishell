/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/05/11 14:32:19 by jpeyron          ###   ########.fr       */
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

void	disp_vars(t_list *vars)
{
	char	**envp;
	size_t	i;

	envp = get_envp(vars);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_iter		*iter;
	t_list		*lexer;
	t_list		*env;
	t_list		*vars;
	t_history	*history;
	t_btree		*ast;
	char		path[4096];

	(void)argc;
	(void)ast;
	(void)argv;

	if (argc != 1)
	{
		disp_error(ARG_ERR);
		return (1);
	}
	else if (!(env = pars_env(envp)))
	{
		disp_error(ENV_ERR);
		return (1);
	}
	else if (!isatty(0))
		return (1);
	if (init_termcap() < 0)
		return (1);
	if (!is_var(env, "PWD"))
		mod_env(&env, "PWD", getcwd(path, 4096));
	else if (!is_var(env, "SHLVL"))
		mod_env(&env, "SHLVL", "1");
	else
		mod_env(&env, "SHLVL", ft_itoa(ft_atoi(get_env_val(env, "SHLVL")) + 1));
	vars = NULL;
	history = read_file(FILE_HISTORY_NAME);
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
		{
			mod_env(&vars, "?", "0");
			continue ;
		}
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
		if (lexer)
		{
			ast = parse_ast(lexer);
		//	btree_apply_infix(ast, disp_node);
		//	printf("\n");
			exec(ast, &env, &vars);
			btree_clear(ast, free_ast_item);
		}
		
		// TEST ENV ET VARS
		//printf("\nENV\n");
		//disp_vars(env);
		//printf("\nVARS\n");
		//disp_vars(vars);
		if (ft_strcmp(iter->line, "exit") == 0)
		{
			lexer_free(lexer, iter);
			break ;
		}
	}
	ft_lstclear(&env, &del_env_elem);
	ft_lstclear(&vars, &del_env_elem);
	free_history(history);
	return (0);
}
