#include "libft.h"

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
}                           t_lem;

/*
** [0] == name
** [1] == x
** [2] == y
**/
void                *ft_malloc(size_t size)
{
    void            *ret;

    ret = malloc(size);
    if (!ret)
        exit(0);
    return (ret);
}

void                free_char_ss(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

t_room              *set_room(char *str, int type)
{
    t_room          *room;
    char            **split;

    room = ft_malloc(sizeof(t_room));
    split = ft_strsplit(str, ' ');
    room->name = ft_strdup(split[0]);
    room->x = ft_atoi(split[1]);
    room->y = ft_atoi(split[2]);
    room->dist = 0;
    room->toggle = 0;
    room->tube = NULL;
    room->start = (type == 1) ? 1 : 0;
    room->end = (type == 2) ? 1 : 0;
    free_char_ss(split);
    return (room);
}

void                add_room(t_room *room, t_listroom **tmp)
{
    t_listroom *list;
    t_listroom *end;

    list = *tmp;
    end = malloc(sizeof(t_listroom));
    end->next = NULL;
    if (list)
    {
        end->start = list;
        end->room = room;
        while (list->next)
        {
            if (ft_strcmp(list->room->name, end->room->name) == 0)
                exit(0);
            if (list->room->x == end->room->x && list->room->y == end->room->y)
                exit(0);
            list->end = end;
            list = list->next;
        }
        list->next = end;
    }
    else
    {
        end->end = NULL;
        end->room = room;
        *tmp = end;
    }
}

void                tube_set(t_tube *tube, t_room *room)
{
    t_tube *tmp;

    tmp = *(&(room->tube));
    if (tmp)
    {
        while (tmp->next)
        {
            if (tmp->room == tube->room)
                exit (0);
            tmp = tmp->next;
        }
        tmp->next = tube;
    }
    else
    {
        room->tube = tube;
    }

}
void                insert_tube(t_room *a, t_room *b)
{
    t_tube *tubea;
    t_tube *tubeb;

    tubea = ft_malloc(sizeof(t_tube));
    tubea->room = b;
    tubeb = ft_malloc(sizeof(t_tube));
    tubeb->room = a;
    tubea->next = NULL;
    tubeb->next = NULL;
    tube_set(tubea, a);
    tube_set(tubeb, b);
}

void                set_dist_room(t_room *room, int dist)
{
    t_tube  *tube;

    tube = *(&(room->tube));
    while (tube)
    {

        if (tube->room->dist == 0 && tube->room->end == 0)
        {
            tube->room->dist = dist + 1;
            set_dist_room(tube->room, dist + 1);
        }
        if (tube->room->dist > dist && tube->room->end == 0)
        {
            tube->room->dist = dist + 1;
            set_dist_room(tube->room, dist + 1);
        }
        tube = tube->next;
    }
}

void                set_dist(t_listroom **tmp)
{
    t_listroom *lst;
    t_listroom *end;

    end = NULL;
    lst = *tmp;
    while (!end || lst) {
        if (lst->room->end == 1)
            return (set_dist_room(lst->room, 0));
        lst = lst->next;
    }
}

void                add_tube(char *str, t_listroom **tmp)
{
    char **split;
    t_room *a;
    t_room *b;
    t_listroom *lst;

    a = NULL;
    b = NULL;
    lst = *tmp;
    split = ft_strsplit(str, '-');
    while (lst)
    {
        if (ft_strcmp(lst->room->name, split[0]) == 0)
            a = lst->room;
        if (ft_strcmp(lst->room->name, split[1]) == 0)
            b = lst->room;
        lst = lst->next;
    }
    if (!a || !b || ft_strcmp(split[0], split[1]) == 0)
        exit(0);
    insert_tube(a, b);
}

void    set_file(t_lem *lem, char *str)
{
    char *ret;
    int i;
    int type;
    int tube;

    tube = 0;
    i = -1;
    ret = ft_get_content_file(str);
    lem->filecontents = ft_strsplit(ret, '\n');
    type = 0;
    while (lem->filecontents[++i])
    {
        printf("TEST %d && %d && %d\n", i, tube, type);
        if (lem->filecontents[i][0] == '#')
        {
            if (ft_strcmp(lem->filecontents[i], "##start") == 0)
                type = 1;
            if (ft_strcmp(lem->filecontents[i], "##end") == 0)
                type = 2;
        }
        else
        {
            if (type >= 0)
            {
                if (tube == 1)
                {
                    add_tube(lem->filecontents[i], &(lem->rooms));
                }
                else
                {
                    add_room(set_room(lem->filecontents[i], type), &(lem->rooms));
                }
                if (type == 2)
                    tube = 1;
            }
            type = 0;
        }
    }
}

char *fill_file(void)
{
    return (strdup("manual_entry.lemin.log"));
}

void  display_room_data(t_room *room)
{
    ft_printf("NAME : %s\n", room->name);
    ft_printf("X : %d\n", room->x);
    ft_printf("Y : %d\n", room->y);
    ft_printf("IS_START : %d\n", room->start);
    ft_printf("IS_END : %d\n", room->end);
    ft_printf("DIST: %d\n", room->dist);
}

void  display_room_link(t_room *room)
{
    t_tube *tube;

    tube = *(&(room->tube));
    while (tube)
    {
        ft_printf("FROM : %s\n", room->name);
        ft_printf("TO : %s\n", tube->room->name);
        tube = tube->next;
    }
}

void display_room_and_tubes(t_lem *lem)
{
    t_listroom *lst;

    lst = *(&(lem->rooms));
    while (lst)
    {
        ft_printf("####NEW ROOM####\n");
        display_room_data(lst->room);
        ft_printf("####LINK ROOM####\n");
        display_room_link(lst->room);
        if (lst->next != NULL)
            ft_printf("####END ROOM####\n\n\n");
        else
            ft_printf("####END ROOM####\n");
        lst = lst->next;
    }
}

int main(int argc, char **argv)
{
    t_lem *lem;

    lem = ft_malloc(sizeof(t_lem));
    lem->rooms = NULL;
    lem->atns = 0;
    if (argc == 2)
        set_file(lem, argv[1]);
    set_dist(&lem->rooms);
    display_room_and_tubes(lem);

}
