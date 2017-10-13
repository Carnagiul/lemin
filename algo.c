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

void				set_dist_room(int dist, t_room *room)
{
	int				i;

	i = 0;
	while (i < liason)
	{
		if (room->room_linked[i]->dist < dist)
			room->room_linked[i]->dist = dist;
		i++;
	}
	i = 0;
	while (i < liason)
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
		if ((t_room *)(list->content)->is_end == 1)
			set_dist_room(1, list->content);
		list = list->next;
	}
}

t_room				*create_new_room(char *name)
{
	t_room			*ret;

	ret = (t_room *)ft_malloc(sizeof(*ret));
	ret = ft_bzero(ret, sizeof(*ret));
	ret->name = ft_strdup(name);
	return (ret);
}

int					main(void)
{
	t_list			*lst;
	t_list			**mem;
	t_room			*ptr;

	lst = NULL;
	mem = &lst;
	ft_lst_push_back(mem, create_new_room("end"), sizeof(t_room));
	ft_lst_push_back(mem, create_new_room("start"), sizeof(t_room));
	ft_lst_push_back(mem, create_new_room("room_1_01"), sizeof(t_room));
	ft_lst_push_back(mem, create_new_room("room_2_02"), sizeof(t_room));
	lst = *mem;
	while (lst)
	{
		ptr = (t_room *)lst->content;
		printf("%s\n", ptr->name);
		lst = lst->next;
	}
}
