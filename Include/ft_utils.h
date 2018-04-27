/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 20:32:05 by piquerue          #+#    #+#             */
/*   Updated: 2016/12/30 23:47:26 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# define ERROR_MSG_DISPLAY "ERROR"
# define ERROR_CUSTOM_MSG 0

int					ft_atoi(char const *str);
char				*ft_itoa(int nb);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_itoa_base(int nb, int base);
int					ft_atoi_base(char *str, int base);
void				*ft_malloc(size_t size);
void				ft_exit_error(void);
void				ft_init_exit_error(void);

#endif
