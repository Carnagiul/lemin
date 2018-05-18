#include "libft.h"

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
	if (!lem->filecontents)
		exit(0);
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
					if (ft_strcmp(rk, lem->filecontents[i]) != 0 || lem->atns <= 0)
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
	if (argc == 1)
		read_entry(lem);
	set_file(lem);
	set_dist(&lem->rooms);
	display_room_and_tubes(lem);
	lem->path = create_quick_path(get_start(&lem->rooms));
	display_path(lem->path);
	//move_ants(lem);
	(void) argv;
	(void) ret;
	_exit(0);
}
