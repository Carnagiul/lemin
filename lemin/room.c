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
	t_listroom *list;

	list = *lst;
	while (list)
	{
		if (list->room->start == 1)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

t_room				*set_room(char *str, int type)
{
	t_room			*room;
	char			**split;

	room = ft_malloc(sizeof(t_room));
	split = ft_strsplit(str, ' ');
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	room->dist = 0;
	room->toggle = 0;
	room->tube = NULL;
	room->start = (type == 1) ? 1 : 0;
	room->end = (type == 2) ? 1 : 0;
	free_char_ss(split);
	return (room);
}
