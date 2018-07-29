/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:16:03 by piquerue          #+#    #+#             */
/*   Updated: 2018/07/30 00:47:26 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					set_dist_room(t_room *room, int dist)
{
	t_tube				*tube;

	tube = *(&(room->tube));
	while (tube)
	{
		if (tube->room->dist == 0 && tube->room->end == 0)
		{
			tube->room->dist = dist + 1;
			set_dist_room(tube->room, dist + 1);
		}
		if (tube->room->dist > dist && tube->room->end == 0)
		{
			tube->room->dist = dist + 1;
			set_dist_room(tube->room, dist + 1);
		}
		tube = tube->next;
	}
}

t_room					*get_end(t_listroom **lst)
{
	t_listroom			*list;

	list = *lst;
	while (list)
	{
		if (list->room->end == 1)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

t_room					*get_start(t_listroom **lst)
{
	t_listroom			*list;

	list = *lst;
	while (list)
	{
		if (list->room->start == 1)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

t_room					*set_room(char *str, int type)
{
	t_room				*room;
	char				**split;

	room = ft_malloc(sizeof(t_room));
	split = ft_strsplit(str, ' ');
	if (!split || !split[0] || !split[1] || !split[2])
		exit(0);
	room->name = ft_strdup(split[0]);
	if (split[0][0] == 'L')
		exit(0);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	if (split[3])
		exit(0);
	room->dist = 0;
	room->toggle = 0;
	room->tube = NULL;
	room->start = (type == 1) ? 1 : 0;
	room->end = (type == 2) ? 1 : 0;
	free_char_ss(split);
	return (room);
}
