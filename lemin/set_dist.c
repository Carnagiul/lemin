/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:16:15 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/18 22:16:16 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				set_dist(t_listroom **tmp)
{
	t_listroom		*lst;
	t_listroom		*end;

	end = NULL;
	lst = *tmp;
	while (!end || lst)
	{
		if (lst->room->end == 1)
			return (set_dist_room(lst->room, 0));
		lst = lst->next;
	}
}
