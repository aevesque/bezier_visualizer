NAME = bezierEV

CC = cc
CFLAGS = -O

RM = rm -rf

SRCS_DIR = srcs
SRCS := main.c\
	nBezier.c\
	inputs.c\
	textinfo.c\
	output.c\
	parsing.c\

OBJ_DIR = objs
OBJ := ${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

TERMGL_PATH :=./termGL

all: ${NAME}

${NAME}: ${TERMGL_PATH}/termGL.a ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ ${TERMGL_PATH}/termGL.a -lm

${OBJ_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
	mkdir ${OBJ_DIR}

${TERMGL_PATH}/termGL.a: ${TERMGL_PATH}/termGL.c
	make -C ${TERMGL_PATH}

${TERMGL_PATH}/termGL.c:
	git submodule init
	git submodule update

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all
