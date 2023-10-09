NAME = minishell
CC = cc
CFLAGS = # -Wall -Werror -Wextra
SRC = main.c utiles.c
OBJ = $(SRC:.c=.o)
RM = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
		make all -C ./libft/
		${CC} ${CFLAGS} ${OBJ} ./libft/libft.a  -o ${NAME}

clean :
	make clean -C ./libft/
	$(RM) $(OBJ)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all