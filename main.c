/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 07:40:08 by piquerue          #+#    #+#             */
/*   Updated: 2018/07/30 00:33:43 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	managecmd(char **argv, int argc, t_lem *lem)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--show_final_path") == 0)
			display_path(lem->path);
		if (ft_strcmp(argv[i], "--show_lemin_data") == 0)
			display_room_and_tubes(lem);
		if (ft_strcmp(argv[i], "--show_lemin_file") == 0)
			display_lemin_file(lem);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_lem	*lem;

	ft_init_exit_error();
	lem = ft_malloc(sizeof(t_lem));
	lem->rooms = NULL;
	lem->atns = 0;
	read_entry(lem);
	set_file(lem);
	verify_lemin(lem);
	set_dist(&lem->rooms);
	lem->path = create_quick_path(get_start(&lem->rooms));
	managecmd(argv, argc, lem);
	move_ants(lem);
	_exit(0);
}
