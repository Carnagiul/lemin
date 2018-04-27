#include "libft.h"

void					free_char_ss(char **str)
{
	int					i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
