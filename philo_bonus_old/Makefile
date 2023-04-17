# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 13:02:52 by marimatt          #+#    #+#              #
#    Updated: 2022/06/07 17:04:13 by marimatt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	    =		philo_bonus

SRC     	=		main.c ft_atoi.c utils.c prints.c philo_life.c philos_utils.c \

CFLAGS  	=		-Wall -Werror -Wextra

SRC_OBJ 	=		$(SRC:.c=.o)

%.o: %.c
			gcc ${CFLAGS} -g -c $< -o $@ 

all:    $(NAME)

$(NAME):	$(SRC_OBJ)
		gcc $(CFLAGS) $(SRC_OBJ) -lpthread -o $(NAME)

clean:
	/bin/rm -f	$(SRC_OBJ)

fclean: clean
	/bin/rm -f	$(NAME)

re: fclean
	make

rec: re
	make clean

.PHONY: re rec fclean clean bonus all
