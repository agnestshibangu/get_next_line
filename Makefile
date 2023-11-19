NAME = get_next_line.a

SRCS = get_next_line_utils.c get_next_line.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

CC = gcc

FLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean:    clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re