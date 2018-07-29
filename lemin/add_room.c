/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:15:03 by piquerue          #+#    #+#             */
/*   Updated: 2018/07/30 00:47:04 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		check_add_room(t_listroom *list, t_listroom *end)
{
	if (ft_strcmp(list->room->name, end->room->name) == 0)
		exit(0);
	if (list->room->x == end->room->x && list->room->y == end->room->y)
		exit(0);
}

void			add_room(t_room *room, t_listroom **tmp)
{
	t_listroom	*list;
	t_listroom	*end;

	list = *tmp;
	end = ft_malloc(sizeof(t_listroom));
	end->next = NULL;
	if (list)
	{
		end->start = list;
		end->room = room;
		while (list->next)
		{
			check_add_room(list, end);
			list->end = end;
			list = list->next;
		}
		list->next = end;
	}
	else
	{
		end->end = NULL;
		end->room = room;
		*tmp = end;
	}
}
