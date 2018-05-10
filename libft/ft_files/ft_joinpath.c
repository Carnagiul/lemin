#include "libft.h"

char				*ft_joinpath(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	if (str[i - 1] != '/')
		str[i++] = '/';
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}
