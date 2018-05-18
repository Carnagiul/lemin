#include "libft.h"

void				set_dist(t_listroom **tmp)
{
	t_listroom		*lst;
	t_listroom		*end;

	end = NULL;
	lst = *tmp;
	while (!end || lst) {
		if (lst->room->end == 1)
			return (set_dist_room(lst->room, 0));
		lst = lst->next;
	}
}
