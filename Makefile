SRC = dinner.c getters_setters.c init.c main.c monitoring.c parsing.c safe_functions.c synchro_utils.c\
		utils.c write.c

NAME = philo

OBJS = ${SRC:.c=.o}

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

MAKE = make -C

all: ${NAME}

${NAME}: ${OBJS}
						cc ${FLAGS} ${OBJS} ${LIBFT} -o ${NAME}
						
clean:
						${RM} ${OBJS}

fclean: clean
						${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

.SILENT: