#include "libft.h"

void		read_entry(t_lem *lem)
{
	char	*ret;
	char	*content;

	content = ft_strnew(1);
	while (get_next_line(0, &ret) == 1)
	{
		content = ft_free_join1(content, ret);
		content = ft_free_join1(content, "\n");
		ft_strdel(&ret);
	}
	if (ft_strlen(content) < 10)
		exit(0);
	lem->filecontents = ft_strsplit(content, '\n');
}

