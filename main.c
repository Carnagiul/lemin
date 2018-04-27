#include "libft.h"

typedef struct              s_tube
{
	struct s_room           *room;
	struct s_tube           *next;
}                           t_tube;

typedef struct              s_room
{
	char                    *name;
	int                     x;
	int                     y;
	int                     start;
	int                     end;
	int                     toggle;
	int                     dist;
	int                     a_id;
	struct s_tube           *tube;
}                           t_room;

typedef struct              s_listroom
{
	struct s_room           *room;
	struct s_listroom       *next;
	struct s_listroom       *end;
	struct s_listroom       *start;
}                           t_listroom;


typedef struct              s_lem
{
	int                     atns;
	char                    *filename;
	char                    **filecontents;
	struct s_listroom       *rooms;
	struct s_tube           *path;
}                           t_lem;

void                free_char_ss(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

t_room              *get_end(t_listroom **lst)
{
	t_listroom *list;

	list = *lst;
	while (list)
	{
		if (list->room->end == 1)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

t_room              *get_start(t_listroom **lst)
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

t_room              *set_room(char *str, int type)
{
	t_room          *room;
	char            **split;

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

void                add_room(t_room *room, t_listroom **tmp)
{
	t_listroom *list;
	t_listroom *end;

	list = *tmp;
	end = malloc(sizeof(t_listroom));
	end->next = NULL;
	if (list)
	{
		end->start = list;
		end->room = room;
		while (list->next)
		{
			if (ft_strcmp(list->room->name, end->room->name) == 0)
				exit(0);
			if (list->room->x == end->room->x && list->room->y == end->room->y)
				exit(0);
			list->end = end;
			list = list->next;
		}
		list->next = end;
	}
	else
	{
		end->end = NULL;
		end->room = room;
		*tmp = end;
	}
}

void                tube_set(t_tube *tube, t_room *room)
{
	t_tube *tmp;

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
void                insert_tube(t_room *a, t_room *b)
{
	t_tube *tubea;
	t_tube *tubeb;

	tubea = ft_malloc(sizeof(t_tube));
	tubea->room = b;
	tubeb = ft_malloc(sizeof(t_tube));
	tubeb->room = a;
	tubea->next = NULL;
	tubeb->next = NULL;
	tube_set(tubea, a);
	tube_set(tubeb, b);
}

void                set_dist_room(t_room *room, int dist)
{
	t_tube  *tube;

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

void                set_dist(t_listroom **tmp)
{
	t_listroom *lst;
	t_listroom *end;

	end = NULL;
	lst = *tmp;
	while (!end || lst) {
		if (lst->room->end == 1)
			return (set_dist_room(lst->room, 0));
		lst = lst->next;
	}
}

void                add_tube(char *str, t_listroom **tmp)
{
	char **split;
	t_room *a;
	t_room *b;
	t_listroom *lst;

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

void    set_file(t_lem *lem)
{
	int i;
	int type;
	int tube;
	int done;
	char *rk;

	tube = 0;
	i = -1;
	type = 0;
	done = 0;
	while (lem->filecontents[++i])
	{
		if (ft_strlen(lem->filecontents[i]) == 0)
			return ;
		if (lem->filecontents[i][0] == '#')
		{
			if (ft_strcmp(lem->filecontents[i], "##start") == 0)
				type = 1;
			if (ft_strcmp(lem->filecontents[i], "##end") == 0)
				type = 2;
		}
		else
		{
			if (done == 0)
			{
				if (type == 0)
				{
					lem->atns = ft_atoi(lem->filecontents[i]);
					rk = ft_itoa(lem->atns);
					if (ft_strcmp(rk, lem->filecontents[i]) != 0)
						exit(0);
					ft_strdel(&rk);
					done = 1;
				}
				else
					exit(0);
			}
			else
			{
				if (type >= 0)
				{
					if (tube == 1)
					{
						add_tube(lem->filecontents[i], &(lem->rooms));
					}
					else
					{
						add_room(set_room(lem->filecontents[i], type), &(lem->rooms));
					}
					if (type == 2)
						tube = 1;
				}
			}
			type = 0;
		}
	}
}

void  display_room_data(t_room *room)
{
	ft_printf("NAME : %s\n", room->name);
	ft_printf("X : %d\n", room->x);
	ft_printf("Y : %d\n", room->y);
	ft_printf("IS_START : %d\n", room->start);
	ft_printf("IS_END : %d\n", room->end);
	ft_printf("DIST: %d\n", room->dist);
}

void  display_room_link(t_room *room)
{
	t_tube *tube;

	tube = *(&(room->tube));
	while (tube)
	{
		ft_printf("FROM : %s\n", room->name);
		ft_printf("TO : %s\n", tube->room->name);
		tube = tube->next;
	}
}

void display_room_and_tubes(t_lem *lem)
{
	t_listroom *lst;

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

void    read_entry(t_lem *lem)
{
	char    *ret;
	char	*content;

	content = ft_strnew(1);
	while (get_next_line(1, &ret) == 1)
	{
		if (ft_strlen(ret) == 0)
		{
			ft_strdel(&ret);
			lem->filecontents = ft_strsplit(content, '\n');
			ft_strdel(&content);
			return ;
		}
		content = ft_free_join1(content, ret);
		content = ft_free_join1(content, "\n");
		ft_strdel(&ret);
	}
}

t_tube  *get_first_min(t_tube **tube, t_tube *f)
{
	t_tube *lst;

	lst = *tube;
	while (lst)
	{
		if (lst->room->dist < f->room->dist)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_tube  *create_quick_path(t_room *room)
{
	t_tube *tube;
	t_tube *ret;
	t_tube *tmp;
	t_tube *actual;

	tube = ft_malloc(sizeof(t_tube));
	tube->room = room;
	tube->next = NULL;
	tmp = *(&(tube));
	while (1)
	{
		ret = get_first_min(&(tmp->room->tube), tmp);
		if (ret == NULL)
			exit(0);
		actual = ft_malloc(sizeof(t_tube));
		actual->next = tmp;
		actual->room = ret->room;
		if (actual->room->end == 1)
			return (actual);
		tmp = actual;
	}
}


void  display_path(t_tube *tb)
{
	t_tube *tube;

	tube = *(&(tb));
	while (tube)
	{
		ft_printf("POS : %s\n", tube->room->name);
		tube = tube->next;
	}
}

void move_ants(t_lem *lem)
{
	t_tube *start;
	t_tube *tmp;
	int     max;
	int     test;

	tmp = *(&(lem->path));
	max = lem->atns;
	test = 1;
	while (test != 0 || lem->atns != 0)
	{
		test = 0;
		start = tmp->next;
		while (start)
		{
			if (start->room->toggle != 0)
			{
				test++;
				ft_printf("MOVE ANTS %d TO END\n", start->room->a_id + 1);
				start->room->a_id = 0;
				start->room->toggle = 0;
			}
			if (start->next)
			{
				if (start->next->room->toggle == 1)
				{
					test++;
					start->next->room->toggle = 0;
					start->room->a_id = start->next->room->a_id;
					start->next->room->a_id = 0;
					start->room->toggle = 1;
					ft_printf("MOVE ANTS %d FROM %s TO %s\n", start->room->a_id + 1, start->next->room->name, start->room->name);
				}
				if (start->next->room->start == 1 && lem->atns > 0)
				{
					test++;
					start->room->a_id = max - lem->atns--;
					start->room->toggle = 1;
					ft_printf("MOVE ANTS %d FROM START\n", start->room->a_id + 1);
				}
			}
			start = start->next;
		}

	}
}

int main(int argc, char **argv)
{
	t_lem *lem;
	char  *ret;

	ft_init_exit_error();
	lem = ft_malloc(sizeof(t_lem));
	lem->rooms = NULL;
	lem->atns = 0;
	if (argc == 2)
	{
		ret = ft_get_content_file(argv[1]);
		if (!ret)
			exit(0);
		lem->filecontents = ft_strsplit(ret, '\n');
		ft_strdel(&ret);
	}
	else
	{
		read_entry(lem);
	}
	set_file(lem);
	set_dist(&lem->rooms);
	display_room_and_tubes(lem);
	lem->path = create_quick_path(get_start(&lem->rooms));
	display_path(lem->path);
	move_ants(lem);
	_exit(0);
}
