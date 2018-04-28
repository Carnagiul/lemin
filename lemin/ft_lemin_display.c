#include "libft.h"

void				display_room_data(t_room *room)
{
	ft_printf("NAME : %s\n", room->name);
	ft_printf("X : %d\n", room->x);
	ft_printf("Y : %d\n", room->y);
	ft_printf("IS_START : %d\n", room->start);
	ft_printf("IS_END : %d\n", room->end);
	ft_printf("DIST: %d\n", room->dist);
}

void				display_room_link(t_room *room)
{
	t_tube			*tube;

	tube = *(&(room->tube));
	while (tube)
	{
		ft_printf("FROM : %s\n", room->name);
		ft_printf("TO : %s\n", tube->room->name);
		tube = tube->next;
	}
}

void				display_room_and_tubes(t_lem *lem)
{
	t_listroom		*lst;

	lst = *(&(lem->rooms));
	ft_printf("You have %d ants\n\n", lem->atns);
	while (lst)
	{
		ft_printf("####NEW ROOM####\n");
		display_room_data(lst->room);
		ft_printf("####LINK ROOM####\n");
		display_room_link(lst->room);
		if (lst->next != NULL)
			ft_printf("####END ROOM####\n\n\n");
		else
			ft_printf("####END ROOM####\n");
		lst = lst->next;
	}
}
