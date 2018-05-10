#include "libft.h"

char				*ft_file_getuser(struct stat stat)
{
	char			*ret;
	t_pswd			*pswd;

	ret = NULL;
	pswd = getpwuid(stat.st_uid);
	if (pswd)
		ret = ft_strdup(pswd->pw_name);
	else
		ret = ft_itoa(stat.st_uid);
	if (ret != NULL)
		return (ret);
	return (ft_strdup("none"));
}
