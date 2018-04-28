#include "libft.h"

void				add_tube(char *str, t_listroom **tmp)
{
	char			**split;
	t_room			*a;
	t_room			*b;
	t_listroom		*lst;

	a = NULL;
	b = NULL;
	lst = *tmp;
	split = ft_strsplit(str, '-');
	while (lst)
	{
		if (ft_strcmp(lst->room->name, split[0]) == 0)
			a = lst->room;
		if (ft_strcmp(lst->room->name, split[1]) == 0)
			b = lst->room;
		lst = lst->next;
	}
	if (!a || !b || ft_strcmp(split[0], split[1]) == 0)
		exit(0);
	free_char_ss(split);
	insert_tube(a, b);
}


void				tube_set(t_tube *tube, t_room *room)
{
	t_tube			*tmp;

	tmp = *(&(room->tube));
	if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->room == tube->room)
				exit (0);
			tmp = tmp->next;
		}
		tmp->next = tube;
	}
	else
	{
		room->tube = tube;
	}
}

void					insert_tube(t_room *a, t_room *b)
{
	t_tube				*tubea;
	t_tube				*tubeb;

	tubea = ft_malloc(sizeof(t_tube));
	tubea->room = b;
	tubeb = ft_malloc(sizeof(t_tube));
	tubeb->room = a;
	tubea->next = NULL;
	tubeb->next = NULL;
	tube_set(tubea, a);
	tube_set(tubeb, b);
}
