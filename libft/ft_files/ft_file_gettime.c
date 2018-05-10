#include "libft.h"

void				ft_file_gettime(time_t timestamp)
{
	time_t			t;
	char			*dt;

	dt = ctime(&timestamp);
	t = time(NULL);
	if (t - timestamp <= 15811200)
		ft_printf("%2.2s %3.3s %5.5s ", &(dt[8]), &(dt[4]), &(dt[11]));
	else
		ft_printf("%2.2s %3.3s %5.4s ", &(dt[8]), &(dt[4]), &(dt[20]));
}
