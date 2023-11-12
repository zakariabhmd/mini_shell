NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c cd.c echo.c exit.c export.c pwd.c bulttin.c help.c check_export.c env.c error.c parse.c\
unset.c search.c command.c free_alloc.c redirection.c test.c expansion.c export_utiles.c cd_utiles.c pipe.c\
red_help.c red_help1.c red_help2.c command_help.c expansion_help.c test_help.c export_utiles1.c red_test.c
OBJ = $(SRC:.c=.o)
RM = rm -rf
readflagnbl = -L/Users/zbabahmi/.brew/opt/readline/lib
readincnbl = -I/Users/zbabahmi/.brew/opt/readline/include/

PARSING_FILES = ./parssing/parssing1.c ./parssing/syntaxerr.c ./parssing/tokenizer.c ./parssing/mainn.c

PARSSING_OBJS = ${PARSING_FILES:.c=.o}

all : ${NAME}

${NAME} : ${OBJ} ${PARSSING_OBJS}
		make all -C ./parssing/libft/
		make all -C ./ft_mallocc/
		${CC} ${readflagnbl} ${CFLAGS} ${PARSSING_OBJS} ${OBJ} ./parssing/libft/libft.a ./ft_mallocc/ft_malloc.a  -lreadline -o ${NAME}

%.o: %.c
		${CC} -I ~/.brew/opt/readline/include/ -c $< -o $@

clean :
	make clean -C ./parssing/libft/
	make clean -C ./ft_mallocc/

	$(RM) $(OBJ)
	${RM} ${PARSSING_OBJS}

fclean : clean
	make fclean -C ./parssing/libft
	make fclean -C ./ft_mallocc/

	$(RM) $(NAME)


re: fclean all
