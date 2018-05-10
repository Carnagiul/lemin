# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: piquerue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 14:20:07 by piquerue          #+#    #+#              #
#    Updated: 2018/05/10 17:03:31 by piquerue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CFLAGS = -Wall -Werror -Wextra -Ofast -Wunreachable-code

C = $(shell find . -type f | grep "\.c")
COUNT = $(shell find . -type f | grep "\.o" | wc -l)
COUNT_MAX = $(shell find . -type f | grep "\.c" | wc -l)
H = $(shell find . -type f | grep "\.h")
O = $(C:%.c=%.o)
T = 0

%.o: %.c $(H)
	@gcc $(CFLAGS) -I Include/ -o $@ -c $<
	$(call plus,$(COUNT), 1)
	@printf "\033[1A\033[KCompiling Source \033[32m%d\033[37m / \033[31m%d\033[37m\n" $(COUNT) $(COUNT_MAX)
$(NAME): check display $(O)
	@gcc -o $(NAME) $(O)
	@printf "\033[1A\033[KCompiling Project \033[33m%s\033[37m\n" $(NAME)

all: $(NAME)

clean: display
	@rm -rf $(O)
fclean: clean
	@rm -f $(NAME)

re: fclean all

display:
	@sh .sh_tool/display.sh

check:
	@sh .sh_tool/check.sh

test:
	@printf "%d fichier .c trouver" $(COUNT)

.PHONY : all clean fclean re






#@printf "\033[1A\033[KCompiling Source \033[32m%s\033[37m =====> \033[31m%s\033[37m\n" $< $@
