 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:13:35 by jules             #+#    #+#             */
/*   Updated: 2021/05/07 13:30:12 by tvachera         ###   ########.fr       */
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
# define SPECIAL_CHARS "'\"<>;| "
# define FILE_HISTORY_NAME ".shitty_history"
# define TERM_NAME "minishit"

/*
**	ERRORS
*/
# define PARS_ERR "parse error\n"
# define ENV_ERR "env error\n"
# define ARG_ERR "to many argunments\n"

/*
** TEMCPAS_KEYS
*/
# define LEFT_ARROW_KEY 1
# define RIGHT_ARROW_KEY 2
# define UP_ARROW_KEY 3
# define DOWN_ARROW_KEY 4
# define BACKSPACE_KEY 5

/*
** COLORS
*/
# define BOLD "\e[1m"
# define NORMAL "\e[0m"
# define DEFAULT_COLOR "\e[39m"
# define WHITE "\e[97m"
# define CYAN "\e[36m"
# define LIGHT_CYAN "\e[96m"
# define DARK_GRAY "\e[90m"

/*
**	EXEC
*/
# define CHEVOUT_SFLAGS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define CHEVR_OFLAGS O_WRONLY | O_CREAT | O_TRUNC
# define DCHEVR_OFLAGS O_WRONLY | O_CREAT | O_APPEND
# define CHEVL_OFLAGS O_RDONLY

#endif
