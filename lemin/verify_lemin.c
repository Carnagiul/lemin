/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_lemin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 07:41:15 by piquerue          #+#    #+#             */
/*   Updated: 2018/06/01 15:41:06 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			verify_lemin(t_lem *lem)
{
	t_listroom	*room;
	int			start;
	int			end;

	start = 0;
	end = 0;
	if (lem->atns == 0)
		exit(0);
	if (lem->rooms == NULL)
		exit(0);
	room = *(&(lem->rooms));
	while (room)
	{
		start += room->room->start;
		end += room->room->start;
		room = room->next;
	}
	if (start == 0 || end == 0)
		exit(0);
}
