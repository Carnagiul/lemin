/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:09:01 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/28 07:41:39 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	move_ants_toggled(t_tube *start, t_tube *tmp, int test)
{
	if (test != 0)
		ft_printf(" ");
	ft_printf("L%d-%s", start->room->a_id + 1, tmp->room->name);
	start->room->a_id = 0;
	start->room->toggle = 0;
	return (1);
}

static int	move_ants_if_next_exist(t_tube *start, t_lem *lem, int max,
		int test)
{
	if (start->next->room->toggle == 1)
	{
		if (test != 0)
			ft_printf(" ");
		start->next->room->toggle = 0;
		start->room->a_id = start->next->room->a_id;
		start->next->room->a_id = 0;
		start->room->toggle = 1;
		ft_printf("L%d-%s", start->room->a_id + 1, start->room->name);
		test = 1;
	}
	else if (start->next->room->start == 1 && lem->atns > 0)
	{
		if (test != 0)
			ft_printf(" ");
		start->room->a_id = max - lem->atns--;
		start->room->toggle = 1;
		ft_printf("L%d-%s\n", start->room->a_id + 1, start->room->name);
		test = -1;
	}
	return (test);
}

static void	move_ants_start_to_end(t_lem *lem, t_tube *tube)
{
	int		id;

	id = 0;
	while (id < lem->atns)
		ft_printf("L%d-%s\n", ++id, tube->room->name);
}

void		move_ants(t_lem *lem)
{
	t_tube	*start;
	t_tube	*tmp;
	int		max;
	int		test;

	max = lem->atns;
	tmp = *(&(lem->path));
	test = 1;
	if (tmp->next->room->start == 1)
		return (move_ants_start_to_end(lem, tmp));
	while (test != 0 || lem->atns != 0)
	{
		test = 0;
		start = tmp;
		while ((start = start->next) != NULL)
		{
			if (start->room->toggle != 0)
				test = move_ants_toggled(start, tmp, test);
			if (start->next)
				test = move_ants_if_next_exist(start, lem, max, test);
		}
		if (test > 0)
			ft_printf("\n");
	}
}
