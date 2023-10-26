NAME = minishell
CC = cc
CFLAGS = #-Wall -Werror -Wextra
SRC = main.c utiles.c cd.c echo.c exit.c export.c pwd.c bulttin.c help.c check_export.c env.c
OBJ = $(SRC:.c=.o)
RM = rm -rf
LDFLAGS="-L/goinfre/zbabahmi/homebrew/opt/readline/lib"
all : ${NAME}

${NAME} : ${OBJ}
		make all -C ./libft/
		${CC}   ${LDFLAGS} ${CFLAGS} ${OBJ} ./libft/libft.a   -lreadline -o ${NAME}

clean :
	make clean -C ./libft/
	$(RM) $(OBJ)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all