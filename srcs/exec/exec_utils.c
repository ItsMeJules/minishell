/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:01:17 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:34:43 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_argv(t_list *cmd)
{
	char	**argv;
	size_t	i;

	argv = malloc(sizeof(char *) * (ft_lstsize(cmd) + 1));
	if (!argv)
		return (0);
	i = 0;
	while (cmd)
	{	
		if (!((t_token *)cmd->content)->str)
			argv[i] = ft_strdup("");
		else
			argv[i] = ft_strdup(((t_token *)cmd->content)->str);
		i++;
		cmd = cmd->next;
	}
	argv[i] = 0;
	return (argv);
}

void	reset_ex(t_exec *ex)
{
	if (ex->fd_in != 0)
	{
		close(ex->fd_in);
		ex->fd_in = 0;
	}
	if (ex->fd_out != 1)
	{
		close(ex->fd_out);
		ex->fd_out = 1;
	}
	if (ex->av)
		ft_free_split(ex->av);
	if (ex->path)
		free(ex->path);
	if (ex->envp)
		ft_free_split(ex->envp);
	ex->av = NULL;
	ex->path = NULL;
	ex->envp = NULL;
	ex->in = -1;
	ex->out = -1;
	ex->expand = false;
}

int	disp_fd_error(char *filename, char *err)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, ": ", 2);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	return (0);
}

bool	set_redir(t_exec *ex, t_node *redir, t_node *file)
{
	t_etype	redir_type;
	char	*filename;

	redir_type = ((t_token *)redir->elem->content)->token;
	filename = ((t_token *)file->elem->content)->str;
	if ((redir_type == CHEV_R || redir_type == D_CHEV_R) && ex->fd_out != 1)
		close(ex->fd_out);
	if (redir_type == CHEV_R)
		ex->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (redir_type == D_CHEV_R)
		ex->fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (redir_type == CHEV_L)
	{
		if (ex->fd_in != 0)
			close(ex->fd_in);
		ex->fd_in = open(filename, O_RDONLY);
	}
	if (ex->fd_out < 0 || ex->fd_in < 0)
	{
		reset_ex(ex);
		return (disp_fd_error(filename, strerror(errno)));
	}
	return (true);
}

void	expand_leafs(t_exec *ex, t_btree *ast, t_list **env, t_list **vars)
{
	t_node	*node;

	if (!ast)
		return ;
	if (ast->right)
		expand_leafs(ex, ast->right, env, vars);
	if (ast->left)
		expand_leafs(ex, ast->left, env, vars);
	if (is_leaf(ast))
	{
		ex->expand = true;
		node = (t_node *)ast->item;
		expand(&node->elem, env, vars, node->type);
	}
}
