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

static int	move_ants_toggled(t_tube *start, t_tube *tmp, int test)
{
	if (test != 0)
		ft_printf(" ");
	ft_printf("L%d-%s", start->room->a_id + 1, tmp->room->name);
	start->room->a_id = 0;
	start->room->toggle = 0;
	return (1);
}

static int	move_ants_toggled_by_next(t_tube *start, int test)
{
	if (test != 0)
		ft_printf(" ");
	start->next->room->toggle = 0;
	start->room->a_id = start->next->room->a_id;
	start->next->room->a_id = 0;
	start->room->toggle = 1;
	ft_printf("L%d-%s", start->room->a_id + 1, start->room->name);
	return (1);
}

static int	move_ants_toggle_it(t_tube *start, t_lem *lem, int max, int test)
{
	if (test != 0)
		ft_printf(" ");
	start->room->a_id = max - lem->atns--;
	start->room->toggle = 1;
	ft_printf("L%d-%s\n", start->room->a_id + 1, start->room->name);
	return (-1);
}

static int	move_ants_if_next_exist(t_tube *start, t_lem *lem, int max, int test)
{
	if (start->next->room->toggle == 1)
		test = move_ants_toggled_by_next(start, test);
	else if (start->next->room->start == 1 && lem->atns > 0)
		test = move_ants_toggle_it(start, lem, max, test);
	return (test);
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
