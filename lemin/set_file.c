/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 00:50:46 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/29 08:42:51 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			set_file_get_command(char *cmd)
{
	if (ft_strcmp(cmd, "##start") == 0)
		return (1);
	if (ft_strcmp(cmd, "##end") == 0)
		return (2);
	return (0);
}

static int			set_file_set_ants(char *cmd, t_lem *lem)
{
	char			*rk;

	lem->atns = ft_atoi(cmd);
	rk = ft_itoa(lem->atns);
	if (ft_strcmp(rk, cmd) != 0 || lem->atns <= 0)
		exit(0);
	ft_strdel(&rk);
	return (1);
}

static int			set_file_set_tube(char *l, int tube, t_lem *lem, int type)
{
	t_listroom		*room;

	tube = is_tube_or_not(l);
	if (type >= 0)
	{
		if (tube == 1)
			add_tube(l, &(lem->rooms));
		else
			add_room(set_room(l, type), &(lem->rooms));
		if (type == 2)
		{
			room = *(&(lem->rooms));
			while (room->next)
			{
				if (room->room->start == 1)
					return (1);
				room = room->next;
			}
			tube = (room->room->start == 1) ? 1 : 0;
		}
	}
	return (tube);
}

static int			set_file_exist(t_lem *lem)
{
	if (!lem->filecontents)
		exit(0);
	return (0);
}

void				set_file(t_lem *lem)
{
	int				i;
	int				type;
	int				tube;
	int				done;

	i = -1;
	type = 0;
	tube = 0;
	done = set_file_exist(lem);
	while (lem->filecontents[++i])
		if (ft_strlen(lem->filecontents[i]) == 0)
			return ;
		else if (lem->filecontents[i][0] == '#')
			type = set_file_get_command(lem->filecontents[i]);
		else
		{
			if (done == 0 && type == 0)
				done = set_file_set_ants(lem->filecontents[i], lem);
			else if (done == 0 && type >= 1)
				exit(0);
			else
				tube = set_file_set_tube(lem->filecontents[i], tube, lem, type);
			type = 0;
		}
}
