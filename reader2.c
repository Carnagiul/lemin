typedef struct			s_lemin
{
	unsigned int		nb_ants;
	struct s_room		*room;
	struct s_allpath	*path;
	struct s_room		*start;
	struct s_room		*end;
}						t_lemin;

typedef struct			s_room
{
	struct s_room		*next;
	char				*name;
	struct s_child		*connector;
	int					passage;
	int					nb_connector;
}						t_room;

typedef struct			s_child
{
	struct s_child		*next;
	struct s_room		*link;
}						t_child;

typedef struct			s_path
{
	struct s_path		*next;
	struct s_room		*path;
}						t_path;

typedef struct			s_allpath
{
	struct s_allpath	*next;
	int					len_path;
	struct s_path		*path;
}						t_allpath;

t_path			*create_path(t_room *room)
{
	t_path		*path;

	path = (t_path *)ft_malloc(sizeof(t_path));
	if (room)
	{
		if (ft_strcmp(room->name, get_start()->name) != 0)
			room->passage = 1;
	}
	path->path = room;
	path->next = NULL;
	return (path);
}

void			ft_push_front_room_path(t_path **path)
{
	t_path		*list;

	list = *path;
	while (list->next)
		list = list->next;
	if (list)
		list->next = create_path(NULL);
	else
		list = create_path(NULL);
}

t_allpath		*create_allpath(void)
{
	t_allpath	*ptr;

	ptr = (t_allpath *)ft_malloc(sizeof(t_allpath));
	ptr->next = NULL;
	ptr->len_path = 0;
	ptr->path = NULL;
	return (ptr);
}

void			ft_push_front_room_apath(t_allpath **all)
{
	t_allpath	*list;

	list = *all;
	while (list->next)
		list = list->next;
	if (ft_verify_path_end(&list) == 1)
	{
		list->next = create_allpath();
		list = list->next;
	}
	ft_push_front_room_path(NULL);
}

int				ft_verify_path_end(t_path **path)
{
	t_path	*list;

	list = *path;
	while (list->next)
		list = list->next;
	if (ft_strcmp(list->path->name, get_start()->name) == 0)
		return (1);
	return (0);
}

int				ft_verify_path_while(t_path **path)
{
	t_path	*ptr;
	t_room	*actual;
	int		exist;

	exist = 0;
	ptr = *path;
	if (ptr->next)
		exist += ft_verify_path_while(&(ptr->next));
	actual = ptr->path;
	ptr = ptr->next;
	while (ptr && actual)
	{
		if (ft_strcmp(ptr->path->name, actual->name) == 0)
			return (exist + 1);
		ptr = ptr->next;
	}
	return (exist + 0);
}

int				room_is_clear(t_room *ptr)
{
	return ((ptr->passage == 0) ? 1 : 0);
}

int			recursive(t_child *ptr)
{
	t_child	*child;
	t_room	*room;

	child = ptr->room->child;
	room = ptr->room;
	if (room->passage == 1)
		return (0);
	if (ft_strcmp(room->name, get_start()->name) == 0)
		return (1);
	while (recursive(child) != 1)
	{
		ptr = ptr->next;
		if (!ptr)
			return (0);
		child = ptr->room->child;
	}
	else
		ptr = ptr->next
}

void			find_path(void)
{
	t_allpath	*list;
	t_room		*end;

	list = (t_allpath *)ft_malloc(sizeof(t_allpath));
	end = get_end();
	
}

void			algo(void)
{
	//Donc afin d'alleger la recherche de base
	//On part de END et on cherche START
	//Des que l'on a trouve START
	//On rajoute le path dans PATH


	//Pour verifier si PATH ne contient pas une case utiliser
	//On passe toutes les cases a 1
	//Si lors de verif, au moins une des cases est a 1 alors on sort. On ne pourra pas l'utiliser
}


	2=======3=======4
	|		|		|
	1===0===1===2===3|5
	|		|
	2		2

if (5 + 3 / 2) < nb_ants
	choose multi_path
else
	choose mono path









void		skip_comment(char *line)
{
	if (ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0)
		return (0);
	if (line[0] == '#')
		return (1);
	return (0);
}

void		read_lemin(void)
{
	char	*line;

	c = 1;
	line = NULL;
	while (c == 1)
	{
		if (line != NULL)
			ft_strdel(&line);
		get_next_line(1, &line);
		c = skip_comment(line);
	}
}
