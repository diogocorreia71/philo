# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 12:00:23 by diodos-s          #+#    #+#              #
#    Updated: 2024/04/02 14:08:16 by diodos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = checks.c init.c main.c routine.c threads.c utils.c

NAME = philo

OBJS = ${SRC:.c=.o}

RM = rm -f

FLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread -I include

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
