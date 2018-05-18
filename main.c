#include "libft.h"

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
				ft_printf("L%d-%s ", start->room->a_id + 1, start->room->name);
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
					ft_printf("L%d-%s ", start->room->a_id + 1, start->room->name);
				}
				else if (start->next->room->start == 1 && lem->atns > 0)
				{
					test++;
					start->room->a_id = max - lem->atns--;
					start->room->toggle = 1;
					ft_printf("L%d-%s\n", start->room->a_id + 1, start->room->name);
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
	move_ants(lem);
	(void) argv;
	(void) ret;
	_exit(0);
}
