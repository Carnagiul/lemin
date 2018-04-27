# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: piquerue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 14:20:07 by piquerue          #+#    #+#              #
#    Updated: 2017/05/19 05:31:41 by piquerue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./a.out

CFLAGS = -Wall -Werror -Wextra -Ofast -Wunreachable-code

C = $(shell find . -type f | grep "\.c")
O = $(C:%.c=%.o)

%.o: %.c
	gcc $(CFLAGS) -I Include/ -o $@ -c $<

$(NAME): $(O)
	gcc -o $(NAME) $(O)
all: $(NAME)

clean:
	rm -rf $(O)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
