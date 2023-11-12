# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoukmat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 23:24:57 by atoukmat          #+#    #+#              #
#    Updated: 2022/11/05 23:25:00 by atoukmat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

SRCS=*.c

OBJECTS=*.o

HEADERS=/*.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS)	$(SRCS) -I $(HEADERS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
