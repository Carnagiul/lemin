#include "libft.h"

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
