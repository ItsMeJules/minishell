/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:13:35 by jules             #+#    #+#             */
/*   Updated: 2021/05/20 15:49:30 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define TERM_ENV_NOT_FOUND "Environment variable 'TERM' not found !\n"
# define TERMCAP_DB_ACCESS "Access to termcap database failed...\n"
# define TERM_TYPE_NOT_DEFINED "Term type '%s' doesn't exist in termcap\
 database.\n"
# define ERR_MALLOC "A malloc has failed...\n"
# define ERR_QUOTE_NOT_CLOSED "The simple quote is not closed !\n"
# define ERR_DQUOTE_NOT_CLOSED "The double quote is not closed !\n"
# define SPECIAL_CHARS "'\"<>;| "
# define FILE_HISTORY_NAME ".shitty_history"
# define TERM_NAME "minishell"

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
# define HOME_KEY 6
# define END_KEY 7
# define CTRL_UP_KEYCOMB 8
# define CTRL_DOWN_KEYCOMB 9

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

#endif
