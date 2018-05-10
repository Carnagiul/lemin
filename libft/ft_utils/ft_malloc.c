#include "libft.h"

void		*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(ft_printf("@RERROR@@: Can't malloc %llu object\n", size));
	return (ret);
}
