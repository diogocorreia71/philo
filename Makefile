NAME = philo
SRC = checks.c init.c main.c routine.c threads.c utils.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -I include

%.o:	%.c
			cc %{CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
					ar rcs philo.a ${OBJS}
					cc ${CFLAGS} philo.a -o ${NAME} -pthread

all: ${NAME}

clean:
			rm -f ${OBJS}

fclean:	clean
			rm -f philo.a philo

re:	fclean	all