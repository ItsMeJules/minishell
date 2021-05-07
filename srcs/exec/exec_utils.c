/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:01:17 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/07 14:47:15 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ex->expand = false;
}

void	disp_fd_error(char *filename, char *err)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, ": ", 2);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
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
		ex->fd_out = open(filename, CHEVR_OFLAGS, CHEVOUT_SFLAGS);
	else if (redir_type == D_CHEV_R)
		ex->fd_out	= open(filename, DCHEVR_OFLAGS, CHEVOUT_SFLAGS);
	else if (redir_type == CHEV_L)
	{
		if (ex->fd_in != 0)
			close(ex->fd_in);
		ex->fd_in = open(filename, CHEVL_OFLAGS);
	}
	if (ex->fd_out < 0 || ex->fd_int < 0)
	{
		disp_fd_error(filemane, strerror(errno));
		return (false);
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
		expand_leafs(ex, ast->right, enc, vars);
	if (is_leaf(ast))
	{
		node = (t_node *)ast->item;
		expand(&node->elem, env, vars, node->type);
		ex->expand = true;
	}
}
