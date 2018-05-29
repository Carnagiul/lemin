/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 20:32:05 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/29 08:41:17 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN_H
# define FT_LEMIN_H

typedef struct				s_tube
{
	struct s_room			*room;
	struct s_tube			*next;
}							t_tube;

typedef struct				s_room
{
	char					*name;
	int						x;
	int						y;
	int						start;
	int						end;
	int						toggle;
	int						dist;
	int						a_id;
	struct s_tube			*tube;
}							t_room;

typedef struct				s_listroom
{
	struct s_room			*room;
	struct s_listroom		*next;
	struct s_listroom		*end;
	struct s_listroom		*start;
}							t_listroom;

typedef struct				s_lem
{
	int						atns;
	char					*filename;
	char					**filecontents;
	struct s_listroom		*rooms;
	struct s_tube			*path;
}							t_lem;

t_room						*get_start(t_listroom **lst);
t_room						*get_end(t_listroom **lst);
t_room						*set_room(char *str, int type);
void						tube_set(t_tube *tube, t_room *room);
void						insert_tube(t_room *a, t_room *b);
void						display_room_data(t_room *room);
void						display_room_link(t_room *room);
void						display_room_and_tubes(t_lem *lem);
t_tube						*get_first_min(t_tube **tube, t_tube *f);
t_tube						*create_quick_path(t_room *room);
void						display_path(t_tube *tb);
void						set_dist_room(t_room *room, int dist);
void						add_tube(char *str, t_listroom **tmp);
void						set_dist(t_listroom **tmp);
void						read_entry(t_lem *lem);
void						add_room(t_room *room, t_listroom **tmp);
void						set_file(t_lem *lem);
void						move_ants(t_lem *lem);
void						verify_lemin(t_lem *lem);
void						display_lemin_file(t_lem *lem);
int							is_tube_or_not(char *l);

#endif
