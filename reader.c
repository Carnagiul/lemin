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

int				verify_path_relink_name(t_path *parent, t_path **child)
{
	t_path		*other;
	int			count;

	count = 0;
	other = *child;
	while (other)
	{
		if (ft_strcmp(parent->path->name, other->path->name) == 0)
			count++;
		if (count >= 2)
			return (0);
		other = other->next;
	}
	return (1);
}

int				verify_path_relink(t_path **path)
{
	t_path		*route;

	route = *path;
	while (route)
	{
		if (verify_path_relink_name(route, &route) == 1)
			return (0);
		route = route->next;
	}
	return (1);
}



void			ft_push_front_allpath(t_allpath *path, t_room *room)
{
	t_allpath	**mem;
	t_allpath	*old;

	mem = &path;
	old = *mem;
	if (old)
	{
		while (old->next)
			old = old->next;
		if (old->path)
		{
			if (ft_strcmp(old->path->path->name, get_end()->name) == 0)
			{
				old->next = (t_allpath *)ft_malloc(sizeof(t_allpath));
				old = old->next;
			}
			ft_push_front_path(old->path, room);
		}
		old = (t_allpath *)ft_malloc(sizeof(t_allpath));
		ft_push_front_path(old->path, room);
	}
}

int				verify_path(t_path *path, t_child **mem)
{
	return (0);
}

int				gen_path(void)
{
	t_allpath	*all;
	t_child		**mem_child;
	t_child		*child;
	t_path		*path;

	all = (t_allpath *)ft_malloc(sizeof(t_allpath));
	mem_child = &(get_end()->connector);
	child = *mem_child;
	while (child)
	{
		if (verify_path(all, &child) == 1)
		{
			ft_push_front_allpath(all, path);
		}
		free_path(path);
		child->next;
	}
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
