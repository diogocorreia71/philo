SRC = dinner.c getters_setters.c init.c main.c parsing.c safe_functions.c synchro_utils.c\
		utils.c write.c

NAME = philo

OBJS = ${SRC:.c=.o}

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

MAKE = make -C

all: ${NAME}

${NAME}: ${OBJS}
						${MAKE}
						cc ${FLAGS} ${OBJS} ${LIBFT} -o ${NAME}
						
clean:
						${RM} ${OBJS}

fclean: clean
						${MAKE} fclean
						${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

.SILENT: