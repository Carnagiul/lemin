#include "libft.h"

static int			set_file_get_command(char *cmd)
{
	if (ft_strcmp(cmd, "##start") == 0)
		return (1);
	if (ft_strcmp(cmd, "##end") == 0)
		return (2);
	return (0);
}

static int			set_file_set_ants(char *cmd, t_lem *lem)
{
	char	*rk;

	lem->atns = ft_atoi(cmd);
	rk = ft_itoa(lem->atns);
	if (ft_strcmp(rk, cmd) != 0 || lem->atns <= 0)
		exit(0);
	ft_strdel(&rk);
	return (1);
}

static int			set_file_set_tube(char *l, int tube, t_lem *lem, int type)
{
	if (type >= 0)
	{
		if (tube == 1)
			add_tube(l, &(lem->rooms));
		else
			add_room(set_room(l, type), &(lem->rooms));
		if (type == 2)
			tube = 1;
	}
	return (tube);
}

static int			set_file_exist(t_lem *lem)
{
	if (!lem->filecontents)
		exit(0);
	return (0);
}

void		set_file(t_lem *lem)
{
	int		i;
	int		type;
	int		tube;
	int		done;

	i = -1;
	type = 0;
	tube = 0;
	done = set_file_exist(lem);
	while (lem->filecontents[++i])
		if (ft_strlen(lem->filecontents[i]) == 0)
			return ;
		else if (lem->filecontents[i][0] == '#')
			type = set_file_get_command(lem->filecontents[i]);
		else
		{
			if (done == 0 && type == 0)
				done = set_file_set_ants(lem->filecontents[i], lem);
			else if (done == 0 && type == 1)
				exit(0);
			else
				tube = set_file_set_tube(lem->filecontents[i], tube, lem, type);
			type = 0;
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
