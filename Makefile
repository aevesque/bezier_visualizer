NAME = bezier

CC = cc
CFLAGS = -O

RM = rm -rf

SRCS_DIR = srcs
SRCS := main.c\
	nBezier.c\
	inputs.c\
	textinfo.c\
	output.c\

OBJ_DIR = objs
OBJ := ${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ ./termGL/termGL.a -lm 

${OBJ_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
	mkdir ${OBJ_DIR}

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all
