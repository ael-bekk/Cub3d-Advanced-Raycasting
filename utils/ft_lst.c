/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:11 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/08 12:34:49 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_map	*ft_lst_last(t_map *lst)
{
	if (!lst)
		return (lst);
	if (!lst->next)
		return (lst);
	return (ft_lst_last(lst->next));
}

void	ft_lst_del_one(t_map *lst, void (*del)(void*))
{
	if (lst)
	{
		if (lst->content)
			del(lst->content);
		free(lst);
	}
}

void	ft_lst_clear(t_map **lst, void (*del)(void*))
{
	t_map	*tmp;

	if (del)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lst_del_one(tmp, del);
		}
	}
}

void	ft_lst_add_back(t_map **lst, t_map *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lst_last(*lst)->next = new;
}

void	ft_lst_add_front(t_map **lst, t_map *new)
{
	new->next = *lst;
	*lst = new;
}
