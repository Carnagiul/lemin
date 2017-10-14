#include "libft.h"

typedef struct		s_room
{
	int				dist;
	int				liason;
	int				occuped;
	struct s_room	**room_linked;
	int				*room_moved;
	int				moved;
	int				is_start;
	int				is_end;
	char			*name;
}					t_room;

typedef struct		s_link
{
	t_room			*one;
	t_room			*two;
	struct s_link	*next;
}					t_link;

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(0);
	return (ret);
}

t_room				*get_room(t_list **addr, char *name)
{
	t_list			*lst;
	t_room			*room;

	lst = *addr;
	while (lst)
	{
		room = (t_room *)lst->content;
		if (ft_strcmp(room->name, name) == 0)
			return (room);
		lst = lst->next;
	}
	return (NULL);
}

void				set_dist_room(int dist, t_room *room)
{
	int				i;

	i = 0;
	while (i < room->liason)
	{	
		if ((room->room_linked[i]->dist > dist ||
			room->room_linked[i]->dist == 0))
		{
			room->room_linked[i]->dist = dist;
		}
		i++;
	}
	i = 0;
	while (i < room->liason)
	{
		if (room->room_linked[i]->dist == dist)
			set_dist_room(dist + 1, room->room_linked[i]);
		i++;
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
		if (((t_room *)(list->content))->is_end == 1)
			((t_room *)(list->content))->dist = 0;
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
	ret->room_linked = NULL;
	ret->room_moved = NULL;
	ret->moved = 0;
	return (ret);
}

t_link				*create_new_link(t_room *one, t_room *two)
{
	t_link			*link;

	link = (t_link *)ft_malloc(sizeof(t_link));
	link->one = one;
	link->two = two;
	link->next = NULL;
	return (link);
}

void				ft_push_back_link_lst(t_link **addr, t_list **rooms, char *name1, char *name2)
{
	t_link			*link;
	t_room			*one;
	t_room			*two;

	link = *addr;
	while (link->next)
		link = link->next;
	one = get_room(rooms, name1);
	two = get_room(rooms, name2);
	if (ft_strcmp(name1, name2) == 0)
		return ;
	if (!one || !two)
		return ;
	if (link)
		link->next = create_new_link(one, two);
	else		
		link = create_new_link(one, two);
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

t_link				*gen_link1(char *name1, char *name2, t_list **addr)
{
	t_link			*link;
	t_room			*one;
	t_room			*two;

	link = (t_link *)ft_malloc(sizeof(t_link));
	one = get_room(addr, name1);
	two = get_room(addr, name2);
	if (ft_strcmp(name1, name2) == 0)
		exit(0);
	link = create_new_link(one, two);
	return (link);
}

void				count_link_for_room(t_list **rooms, t_link **link)
{
	t_link			*l;
	t_list			*lst;
	t_room			*room;

	lst = *rooms;
	while (lst)
	{
		room = (t_room *)lst->content;
		l = *link;
		while (l)
		{
			if (ft_strcmp(room->name, l->one->name) == 0 || ft_strcmp(room->name, l->two->name) == 0)
				room->liason = room->liason + 1;
			l = l->next;
		}
		lst = lst->next;
	}
}

void				generate_room_array(t_list **rooms, t_link **link)
{
	t_link			*l;
	t_list			*lst;
	t_room			*room;
	int				i;

	lst = *rooms;
	while (lst)
	{
		room = (t_room *)lst->content;
		if (room->liason > 0)
		{
			room->room_linked = (t_room **)ft_malloc(sizeof(t_room *) * room->liason);
			room->room_moved = (int *)ft_malloc(sizeof(int ) * room->liason);
			i = 0;
			l = *link;
			while (l)
			{
				if (ft_strcmp(room->name, l->one->name) == 0 || ft_strcmp(room->name, l->two->name) == 0)
				{
					room->room_linked[i] = (t_room *)ft_malloc(sizeof(t_room));
					room->room_moved[i] = 0;
					room->room_linked[i++] = (ft_strcmp(room->name, l->one->name) != 0) ? l->one : l->two;
				}
				l = l->next;
			}
		}
		lst = lst->next;

	}
}

void				move_toward_end(t_list *lst)
{
	t_room			*room;
	int				i;

	i = 0;
	room = (t_room *)lst->content;
	if (room->is_end == 1 || room->is_start == 1)
		return ;
	if (room->occuped >= 1)
	{
		while (i < room->liason)
		{
			if (room->room_linked[i]->dist < room->dist)
			{
				if ((room->room_linked[i]->occuped == 0 ||
					room->room_linked[i]->is_end) &&
					room->moved == 0)
					{
						room->room_linked[i]->occuped = room->room_linked[i]->occuped + 1;
						room->occuped = room->occuped - 1;
						room->moved = 1;
						ft_printf("MOVE 1: 1 ants move from %s to %s\n", room->name, room->room_linked[i]->name);
					}
			}
			i++;
		}
	}
}

int					after_is_better(t_room *room, int i)
{
	int				cpy;

	cpy = i;
	i++;
	while (i < room->liason)
	{
			if (room->room_linked[i]->dist < room->room_linked[cpy]->dist)
			{
				if ((room->room_linked[i]->occuped == 0 ||
					room->room_linked[i]->is_end == 1) &&
					(room->moved == 0 && room->room_moved[i] == 0) &&
					room->room_linked[i]->is_start == 0 &&
					room->occuped >= 1
					)
					{
						return (1);
					}
			}
			i++;
	}
	return (0);
}

void				move_toward_end2(t_list *lst)
{
	t_room			*room;
	int				i;

	i = 0;
	room = (t_room *)lst->content;
	if (room->is_end == 1)
		return ;
	if (room->occuped >= 1)
	{
		while (i < room->liason)
		{
			if (room->room_linked[i]->dist <= room->dist)
			{
				if ((room->room_linked[i]->occuped == 0 ||
					room->room_linked[i]->is_end == 1) &&
					(room->moved == 0 && room->room_moved[i] == 0) &&
					room->room_linked[i]->is_start == 0 &&
					room->occuped >= 1 && after_is_better(room, i) == 0
					)
					{
						room->room_linked[i]->occuped = room->room_linked[i]->occuped + 1;
						room->room_linked[i]->moved = 1;
						room->room_moved[i] = 1;
						room->occuped = room->occuped - 1;
						if (room->is_start == 0)
							room->moved = 1;		
						if (room->is_start == 0)
							room->moved = 1;						
						ft_printf("MOVE 2: 1 ants move from %s to %s\n", room->name, room->room_linked[i]->name);
					}
			}
			i++;
		}
	}
}

void				move_ants(t_list **lst)
{
	t_list			*one;
	t_list			*two;
	t_room			*room;

	one = *lst;
	while (one)
	{
		room = ((t_room *)one->content);
		room->moved = 0;
		while (room->moved < room->liason)
			room->room_moved[room->moved++] = 0;
		room->moved = 0;
		one = one->next;
	}
	while (one)
	{
		two = *lst;
		while (two)
		{
			move_toward_end(two);
			two = two->next;
		}
		one = one->next;
	}
	one = *lst;
	while (one)
	{
		two = *lst;
		while (two)
		{
			move_toward_end2(two);
			two = two->next;
		}
		one = one->next;
	}
}

int					main(void)
{
	t_room			*lst;
	t_room			*lst2;
	t_list			*test;
	//t_list			*test2;
	t_link			*link;
	//t_link			*cpy;

	lst = create_new_room("end");
	lst->is_end = 1;
	lst2 = create_new_room("start");
	lst2->is_start = 1;
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
	link = gen_link1("001", "002", &test);
	ft_push_back_link_lst(&link, &test, "002", "003");
	ft_push_back_link_lst(&link, &test, "003", "004");
	ft_push_back_link_lst(&link, &test, "004", "005");
	ft_push_back_link_lst(&link, &test, "005", "006");
	ft_push_back_link_lst(&link, &test, "006", "007");
	ft_push_back_link_lst(&link, &test, "007", "008");
	ft_push_back_link_lst(&link, &test, "008", "009");
	ft_push_back_link_lst(&link, &test, "009", "010");
	ft_push_back_link_lst(&link, &test, "010", "011");
	ft_push_back_link_lst(&link, &test, "start", "011");
	ft_push_back_link_lst(&link, &test, "end", "001");
	ft_push_back_link_lst(&link, &test, "end", "005");
	ft_push_back_link_lst(&link, &test, "005", "011");
	ft_push_back_link_lst(&link, &test, "end", "start");
	ft_push_back_link_lst(&link, &test, "end", "002");
	ft_push_back_link_lst(&link, &test, "end", "003");
	ft_push_back_link_lst(&link, &test, "end", "004");
	ft_push_back_link_lst(&link, &test, "start", "001");
	ft_push_back_link_lst(&link, &test, "start", "002");
	ft_push_back_link_lst(&link, &test, "start", "003");
	ft_push_back_link_lst(&link, &test, "start", "004");

	count_link_for_room(&test, &link);
	generate_room_array(&test, &link);

	calc_dist_from_room(&test);

	lst2->occuped = 100;
	int ants;
	int	i;

	i = 0;
	ants = lst2->occuped;
	while (lst->occuped != ants)
	{
		ft_printf("Tour %d : \n", i);
		move_ants(&test);
		ft_printf("\nFin du tour %d\n\n", i);

		i++;
	}
	printf("start == %d || end == %d || i == %d\n", lst2->occuped, lst->occuped, i);

	/*
	test2 = test;
	cpy = link;

	int	id;
	id = 0;
	while (test2)
	{
		printf("room %d [%s] dist from end %d\n", ++id, ((t_room *)test2->content)->name, ((t_room *)test2->content)->dist);
		test2 = test2->next;
	}
	while (cpy)
	{
		printf("room %s ==> %s linked\n", cpy->one->name, cpy->two->name);
		cpy = cpy->next;
	}
	*/
}
