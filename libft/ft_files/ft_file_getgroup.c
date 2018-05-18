#include "libft.h"

char				*ft_file_getgroup(struct stat stat)
{
	char			*ret;
	t_group			*grp;

	ret = NULL;
	grp = getgrgid(stat.st_gid);
	if (grp)
		ret = ft_strdup(grp->gr_name);
	else
		ret = ft_itoa(stat.st_gid);
	if (ret != NULL)
		return (ret);
	return (ft_strdup("none"));
}
