#include "libft.h"

typedef struct		s_room
{
	int				dist;
	int				liason;
	int				occuped;
	struct s_room	**room_linked;
	int				is_start;
	int				is_end;
	char			*name;
}					t_room;

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(0);
	return (ret);
}

void				set_dist_room(int dist, t_room *room)
{
	int				i;

	i = 0;
	while (i < room->liason)
	{
		if (room->room_linked[i]->dist < dist)
			room->room_linked[i]->dist = dist;
		i++;
	}
	i = 0;
	while (i < room->liason)
	{
		if (room->room_linked[i]->dist == dist)
			set_dist_room(dist + 1, room->room_linked[i]);
	}
}

void				calc_dist_from_room(t_list **mem)
{
	t_list			*list;

	list = *mem;
	while (list)
	{
		if (((t_room *)(list->content))->is_end == 1)
			set_dist_room(1, list->content);
		list = list->next;
	}
}

t_room				*create_new_room(char *name)
{
	t_room			*ret;

	ret = (t_room *)ft_malloc(sizeof(t_room));
	ret->name = ft_strdup(name);
	ret->dist = 0;
	ret->liason = 0;
	ret->occuped = 0;
	ret->is_start = 0;
	ret->is_end = 0;
	return (ret);
}

t_list				*ft_create_lst_room(t_room *room)
{
	t_list			*lst;

	lst = (t_list *)ft_malloc(sizeof(t_list));
	lst->content = (t_room *)ft_malloc(sizeof(t_room));
	lst->content = room;
	lst->next = NULL;
	return (lst);
}

void				ft_push_back_room_lst(t_list **addr, t_room *room)
{
	t_list			*lst;

	lst = *addr;
	while (lst->next)
		lst = lst->next;
	if (lst)
		lst->next = ft_create_lst_room(room);
	else
		lst = ft_create_lst_room(room);
}

int					main(void)
{
	t_room			*lst;
	t_room			*lst2;
	t_list			*test;
	t_list			*test2;

	lst = create_new_room("end");
	lst2 = create_new_room("start");
	test = ft_create_lst_room(lst);
	ft_push_back_room_lst(&test, lst2);
	ft_push_back_room_lst(&test, create_new_room("001"));
	ft_push_back_room_lst(&test, create_new_room("002"));
	ft_push_back_room_lst(&test, create_new_room("003"));
	ft_push_back_room_lst(&test, create_new_room("004"));
	ft_push_back_room_lst(&test, create_new_room("005"));
	ft_push_back_room_lst(&test, create_new_room("006"));
	ft_push_back_room_lst(&test, create_new_room("007"));
	ft_push_back_room_lst(&test, create_new_room("008"));
	ft_push_back_room_lst(&test, create_new_room("009"));
	ft_push_back_room_lst(&test, create_new_room("010"));
	ft_push_back_room_lst(&test, create_new_room("011"));
	test2 = test;
	int	id;
	id = 0;
	while (test2)
	{
		printf("room %d [%s]\n", ++id, ((t_room *)test2->content)->name);
		test2 = test2->next;
	}
}
