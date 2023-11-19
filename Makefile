NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c cd.c echo.c exit.c export.c pwd.c bulttin.c help.c env.c error.c parse.c pipe1.c mainn1.c  main1.c\
unset.c search.c command.c free_alloc.c redirection.c test.c expansion.c export_utiles.c cd_utiles.c pipe.c\
red_help.c red_help1.c red_help2.c command_help.c expansion_help.c test_help.c export_utiles1.c red_test.c\
main2.c
OBJ = $(SRC:.c=.o)
RM = rm -rf
readflagnbl = -L/Users/zbabahmi/.brew/opt/readline/lib
readincnbl = -I/Users/zbabahmi/.brew/opt/readline/include/

PARSING_FILES = parssing1.c syntaxerr.c tokenizer.c mainn.c tokenizer1.c parssing2.c parssing3.c parssing4.c\
parssing5.c

PARSSING_OBJS = ${PARSING_FILES:.c=.o}

all : ${NAME}

${NAME} : ${OBJ} ${PARSSING_OBJS}
		make all -C ./libft/
		make all -C ./ft_mallocc/
		${CC} ${readflagnbl} ${CFLAGS} ${PARSSING_OBJS} ${OBJ} ./libft/libft.a ./ft_mallocc/ft_malloc.a  -lreadline -o ${NAME}

%.o: %.c
		${CC} -I ~/.brew/opt/readline/include/ -c $< -o $@

clean :
	make clean -C ./libft/
	make clean -C ./ft_mallocc/

	$(RM) $(OBJ)
	${RM} ${PARSSING_OBJS}

fclean : clean
	make fclean -C ./libft
	make fclean -C ./ft_mallocc/

	$(RM) $(NAME)


re: fclean all
