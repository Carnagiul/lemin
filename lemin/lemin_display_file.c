#include "libft.h"

void		display_lemin_file(t_lem *lem)
{
	int		i;

	i = 0;
	while (lem->filecontents[i])
		ft_printf("%s\n", lem->filecontents[i++]);
}
