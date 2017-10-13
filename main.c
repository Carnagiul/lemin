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
	ret->room_linked = NULL;
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

int					main(void)
{
	t_room			*lst;
	t_room			*lst2;
	t_list			*test;
	t_list			*test2;
	t_link			*link;
	t_link			*cpy;

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
	calc_dist_from_room(&test);
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
}
