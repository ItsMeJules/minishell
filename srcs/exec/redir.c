/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:33:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/06 17:42:07 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define CHEVOUT_SFLAGS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define CHEVR_OFLAGS O_WRONLY | O_CREAT | O_TRUNC
# define DCHEVR_OFLAGS O_WRONLY | O_CREAT | O_APPEND
# define CHEVL_OFLAGS O_RDONLY

char	*get_filename(t_node *leaf, t_list **env, t_list **vars)
{
	expand(&leaf->elem, env, vars);
	return (((t_token *)leaf->elem->content)->str);	
}

bool	set_redir(t_exec *ex, t_btree *ast, t_list **env, t_list **vars)
{
	t_etype	redir_type;
	char	*filename;

	redir_type = ((t_token *)((t_node *)ast->item)->elem->content)->token;
	filename = get_filename(ast->left->item);
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
		return (false);
	}
	return (true);
}
