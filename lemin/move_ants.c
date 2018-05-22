/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:09:01 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/19 01:09:11 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	move_ants_toggled(t_tube *start)
{
	ft_printf("L%d-%s ", start->room->a_id + 1, start->room->name);
	start->room->a_id = 0;
	start->room->toggle = 0;
	return (1);
}

static int	move_ants_toggled_by_next(t_tube *start)
{
	start->next->room->toggle = 0;
	start->room->a_id = start->next->room->a_id;
	start->next->room->a_id = 0;
	start->room->toggle = 1;
	ft_printf("L%d-%s ", start->room->a_id + 1, start->room->name);
	return (1);
}

static int	move_ants_toggle_it(t_tube *start, t_lem *lem, int max)
{
	start->room->a_id = max - lem->atns--;
	start->room->toggle = 1;
	ft_printf("L%d-%s\n", start->room->a_id + 1, start->room->name);
	return (1);
}

void		move_ants(t_lem *lem)
{
	t_tube	*start;
	t_tube	*tmp;
	int		max;
	int		test;

	tmp = *(&(lem->path));
	max = lem->atns;
	test = 1;
	while (test != 0 || lem->atns != 0)
	{
		test = 0;
		start = tmp->next;
		while (start)
		{
			if (start->room->toggle != 0)
				test = move_ants_toggled(start);
			if (start->next)
			{
				if (start->next->room->toggle == 1)
					test = move_ants_toggled_by_next(start);
				else if (start->next->room->start == 1 && lem->atns > 0)
					test = move_ants_toggle_it(start, lem, max);
			}
			start = start->next;
		}
	}
}