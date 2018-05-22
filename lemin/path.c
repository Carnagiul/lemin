/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:15:49 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/18 22:15:50 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tube				*get_first_min(t_tube **tube, t_tube *f)
{
	t_tube			*lst;

	lst = *tube;
	while (lst)
	{
		if (lst->room->dist < f->room->dist)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_tube				*create_quick_path(t_room *room)
{
	t_tube			*tube;
	t_tube			*ret;
	t_tube			*tmp;
	t_tube			*actual;

	tube = ft_malloc(sizeof(t_tube));
	tube->room = room;
	tube->next = NULL;
	tmp = *(&(tube));
	while (1)
	{
		ret = get_first_min(&(tmp->room->tube), tmp);
		if (ret == NULL)
			exit(0);
		actual = ft_malloc(sizeof(t_tube));
		actual->next = tmp;
		actual->room = ret->room;
		if (actual->room->end == 1)
			return (actual);
		tmp = actual;
	}
}

void				display_path(t_tube *tb)
{
	t_tube			*tube;
	int				id;

	id = 0;
	tube = *(&(tb));
	while (tube)
	{
		ft_printf("POS %d: %s\n", id++, tube->room->name);
		tube = tube->next;
	}
}
