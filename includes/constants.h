 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:13:35 by jules             #+#    #+#             */
/*   Updated: 2021/04/21 15:06:07 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define TERM_ENV_NOT_FOUND "Environment variable 'TERM' not found !\n"
# define TERMCAP_DB_ACCESS "Access to termcap database failed...\n"
# define TERM_TYPE_NOT_DEFINED "Term type '%s' doesn't exist in termcap"\
	" database.\n"
# define ERR_MALLOC "A malloc has failed...\n"
# define ERR_QUOTE_NOT_CLOSED "The simple quote is not closed !\n"
# define ERR_DQUOTE_NOT_CLOSED "The double quote is not closed !\n"
# define SPECIAL_CHARS "'\"<>;|"
# define FILE_HISTORY_NAME ".shitty_history"
# define TERM_NAME "minishit"

/*
**	ERRORS
*/
# define ERR_PARS "parse error\n"

/*
** TEMCPAS_KEYS
*/
# define LEFT_ARROW_KEY 1
# define RIGHT_ARROW_KEY 2
# define UP_ARROW_KEY 3
# define DOWN_ARROW_KEY 4
# define BACKSPACE_KEY 5

#endif
