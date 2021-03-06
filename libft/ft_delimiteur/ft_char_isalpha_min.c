/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_isalpha_min.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 21:09:03 by piquerue          #+#    #+#             */
/*   Updated: 2016/12/18 20:24:32 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_isalpha_min(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
