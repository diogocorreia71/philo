SRC = checks.c init.c main.c routine.c threads.c utils.c

NAME = philo

OBJS = ${SRC:.c=.o}

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread -I include

MAKE = make -C

all: ${NAME}

${NAME}: ${OBJS}
						cc ${FLAGS} ${OBJS} -o ${NAME}
						
clean:
						${RM} ${OBJS}

fclean: clean
						${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

.SILENT: