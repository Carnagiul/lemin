#include "libft.h"

void		verify_lemin(t_lem *lem)
{
	if (lem->atns == 0)
		exit(0);
	if (lem->rooms == NULL)
		exit(0);
}
