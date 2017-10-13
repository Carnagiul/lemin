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

	printf("Try malloc room\n");
	ret = (t_room *)ft_malloc(sizeof(t_room));
	printf("Try malloc room name\n");
	ret->name = ft_strdup(name);
	ret->dist = 0;
	ret->liason = 0;
	ret->occuped = 0;
	ret->is_start = 0;
	ret->is_end = 0;
	return (ret);
}

int					main(void)
{
	t_room			*lst;
	t_room			*lst2;
	t_list			*test;
	t_list			*test2;

	lst = create_new_room("end");
	printf("malloc 1 done!\n");
	lst2 = create_new_room("start");
	printf("malloc 2 done!\n");
	test = (t_list *)malloc(sizeof(t_list));
	if (test)
	{
		test->content = (t_room *)malloc(sizeof(t_room));
		test->content = lst;
		test->next = (t_list *)malloc(sizeof(t_list));
		if (test->next)
		{
			test->next->content = (t_room *)malloc(sizeof(t_room));
			test->next->content = lst2;
			test->next->next = NULL;
		}
	}
	test2 = test;
	int	id;
	id = 0;
	while (test2)
	{
		printf("room %d [%s]\n", id++, ((t_room *)test2->content)->name);
		test2 = test2->next;
	}
}
