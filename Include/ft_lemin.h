
#ifndef FT_LEMIN_H
# define FT_LEMIN_H

typedef struct              s_tube
{
	struct s_room           *room;
	struct s_tube           *next;
}                           t_tube;

typedef struct              s_room
{
	char                    *name;
	int                     x;
	int                     y;
	int                     start;
	int                     end;
	int                     toggle;
	int                     dist;
	int                     a_id;
	struct s_tube           *tube;
}                           t_room;

typedef struct              s_listroom
{
	struct s_room           *room;
	struct s_listroom       *next;
	struct s_listroom       *end;
	struct s_listroom       *start;
}                           t_listroom;


typedef struct              s_lem
{
	int                     atns;
	char                    *filename;
	char                    **filecontents;
	struct s_listroom       *rooms;
	struct s_tube           *path;
}                           t_lem;

#endif
