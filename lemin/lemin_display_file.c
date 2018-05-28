/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_display_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 07:40:52 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/28 07:40:54 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		display_lemin_file(t_lem *lem)
{
	int		i;

	i = 0;
	while (lem->filecontents[i])
		ft_printf("%s\n", lem->filecontents[i++]);
}
