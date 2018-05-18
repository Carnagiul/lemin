/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:15:56 by piquerue          #+#    #+#             */
/*   Updated: 2018/05/18 22:16:30 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		read_entry(t_lem *lem)
{
	char	*ret;
	char	*content;

	content = ft_strnew(1);
	while (get_next_line(0, &ret) == 1)
	{
		content = ft_free_join1(content, ret);
		content = ft_free_join1(content, "\n");
		ft_strdel(&ret);
	}
	if (ft_strlen(content) < 10)
		exit(0);
	lem->filecontents = ft_strsplit(content, '\n');
}
