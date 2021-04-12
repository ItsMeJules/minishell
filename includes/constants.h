/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:13:35 by jules             #+#    #+#             */
/*   Updated: 2021/04/12 14:58:45 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define TERM_ENV_NOT_FOUND "Environment variable 'TERM' not found !\n"
# define TERMCAP_DB_ACCESS "Access to termcap database failed...\n"
# define TERM_TYPE_NOT_DEFINED "Term type '%s' doesn't exist in termcap"\
	" database.\n"
# define ERR_MALLOC "A malloc has failed..."
# define ERR_QUOTE_NOT_CLOSED "The simple quote is not closed !"
# define ERR_DQUOTE_NOT_CLOSED "The double quote is not closed !"
# define SPECIAL_CHARS "'\"<>;|"

/*
** TERMCAPS UTILES
**
** ch: Deplace le curseur a la colonne C sur la meme ligne
** dc (pas sur): Supprime un char a la position du curseur
** dl: Supprime la ligne entiere /!\ Meme le prompt minishit>
** dm: Entre dans le mode suppression
** ed: Quitte le mode suppression
** im: Entre dans le mode insertion
** ic (ptet pas utile): Insere un char a la position du curseur
** kb: Termcap renvoye par backspace (suppression)
** kd: Termcap renvoye par la fleche du bas
** kl: Termcap renvoye par la fleche de gauche
** kr: Termcap renvoye par la flceche de droite
** ku: Termcap renvoye par la flceche du haut
** le & nd: bouge le curseur une colonne a gauche/droite
*/

#endif
