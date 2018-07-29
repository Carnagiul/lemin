/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:15:17 by piquerue          #+#    #+#             */
/*   Updated: 2018/07/30 00:51:48 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						is_tube_or_not(char *l)
{
	int					c;
	int					space;
	int					six;

	space = 0;
	six = 0;
	c = -1;
	printf("%s\n", l);
	while (l[++c])
	{
		if (l[c] == ' ')
			space++;
		if (l[c] == '-')
			six++;
	}
	if (space == 2)
		return (0);
	if (six == 1)
		return (1);
	exit(0);
}

void					add_tube(char *str, t_listroom **tmp)
{
	char				**split;
	t_room				*a;
	t_room				*b;
	t_listroom			*lst;

	a = NULL;
	b = NULL;
	lst = *tmp;
	split = ft_strsplit(str, '-');
	if (!split || !split[0] || !split[1])
		exit(0);
	if (!lst)
		exit(0);
	while (lst)
	{
		if (ft_strcmp(lst->room->name, split[0]) == 0)
			a = lst->room;
		if (ft_strcmp(lst->room->name, split[1]) == 0)
			b = lst->room;
		lst = lst->next;
	}
	if (!a || !b || ft_strcmp(split[0], split[1]) == 0)
		return (free_char_ss(split));
	free_char_ss(split);
	insert_tube(a, b);
}

void					tube_set(t_tube *tube, t_room *room)
{
	t_tube				*tmp;

	tmp = *(&(room->tube));
	if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->room == tube->room)
				return ;
			tmp = tmp->next;
		}
		if (tmp->room == tube->room)
			return ;
		tmp->next = tube;
	}
	else
		room->tube = tube;
}

void					insert_tube(t_room *a, t_room *b)
{
	t_tube				*tubea;
	t_tube				*tubeb;

	tubea = ft_malloc(sizeof(t_tube));
	tubea->room = b;
	tubeb = ft_malloc(sizeof(t_tube));
	tubeb->room = a;
	tubea->next = NULL;
	tubeb->next = NULL;
	tube_set(tubea, a);
	tube_set(tubeb, b);
}
