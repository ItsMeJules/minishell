/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:25:18 by tvachera          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/14 16:14:47 by tvachera         ###   ########.fr       */
=======
/*   Updated: 2021/04/14 17:40:37 by jpeyron          ###   ########.fr       */
>>>>>>> cmd_history
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHAIN_LIST_H
# define FT_CHAIN_LIST_H

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lst_sort(t_list **begin_list, int (*cmp)());
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *)
				, void (*del)(void *));
<<<<<<< HEAD
void			ft_lstremove_if(t_list **begin_list, void *data_ref
				, int (*cmp)(), void (*free_fct)(void *));
=======
t_list			*ft_lstat(t_list *begin_list, unsigned int nbr);
>>>>>>> cmd_history

#endif
