#include "libft.h"

int			ft_unix_string_display_ii(int wc)
{
	int		c, d;

	c = (wc >> 6) + 0XC0;
	d = (wc & 0x3F) + 0X80;
	write(1, &c, 1);
	write(1, &d, 1);
	return (2);
}

int			ft_unix_string_display_iii(int wc)
{
	int	b;
	int	c;
	int	d;

	b = (wc >> 12) + 0XE0;
	c = ((wc >> 6) & 0x3F) + 0X80;
	d = (wc & 0x3F) + 0X80;
	write(1, &b, 1);
	write(1, &c, 1);
	write(1, &d, 1);
	return (3);
}

int			ft_unix_string_display_iv(int wc)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = (wc >> 18) + 0xF0;
	b = ((wc >> 12) & 0x3F) + 0X80;
	c = ((wc >> 6) & 0x3F) + 0X80;
	d = (wc & 0x3F) + 0X80;
	write(1, &a, 1);
	write(1, &b, 1);
	write(1, &c, 1);
	write(1, &d, 1);
	return (4);
}