#include "libft.h"

void	ft_init_exit_error(void)
{
	if (ERROR_CUSTOM_MSG == 1)
		atexit(&ft_exit_error);
}
