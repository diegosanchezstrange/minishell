NAME	= minishell

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=32 #-g3 -fsanitize=address

SRCS	= main.c

OBJS	= ${SRCS:.c=.o}

SRCS_DIR = src
OBJS_DIR = obj

LIBFT_NAME	= libft.a

LIBFT	= lib/libft/

SRCS_PATHS 	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_PATHS 	= $(addprefix $(OBJS_DIR)/, $(OBJS))

RM		= rm -rf

OS		:= $(shell uname -s)

LIB_LNK	= -L ${LIBFT}

INCLUDES = -I ./${LIBFT}inc -I ./inc

all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@ 

$(NAME): ${LIBFT_NAME} ${OBJS_DIR} ${OBJS_PATHS} 
	${CC} ${CFLAGS} ${LIB_LNK} ${OBJS_PATHS} -o ${NAME} -lft -lreadline

${LIBFT_NAME} :
	make -C ${LIBFT}
	cp ${LIBFT}/${LIBFT_NAME} .

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) 2> /dev/null

clean:
		@${RM} *.a ${OBJS_DIR}/*.o *.dSYM

fclean:		clean
		@${RM} ${NAME}

re:		fclean all

.PHONY:	clean re fclean all
