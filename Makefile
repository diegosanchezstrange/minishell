NAME	= minishell

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=32 -g3 -fsanitize=address

SRCS_MAIN	= main.c

SRCS_LEXER	= tokens.c classify_tokens.c utils.c parse_env_vars.c parse_quotes.c

SRCS_PARSER	= parser.c parse_command.c

SRCS_BINARY = ft_pwd.c ft_echo.c ft_exit.c ft_env.c ft_unset.c ft_export.c

SRCS_AST	= ast_new.c ast_add_right.c ast_add_left.c ast_get_last_r.c ast_get_last_l.c ast_append_left.c ast_append_right.c astsize_r.c

SRCS_EXEC	= exec.c

SRCS	= $(SRCS_MAIN) \
		  $(addprefix lexer/, $(SRCS_LEXER)) \
		  $(addprefix binaries/, $(SRCS_BINARY)) \
		  $(addprefix ast/, $(SRCS_AST)) \
		  $(addprefix executer/, $(SRCS_EXEC)) \
		  $(addprefix parser/, $(SRCS_PARSER))

OBJS	= ${SRCS:.c=.o}

SRCS_DIR = src
OBJS_DIR = obj

OBJS_DIRS = $(OBJS_DIR) \
			$(addprefix $(OBJS_DIR)/, lexer) \
			$(addprefix $(OBJS_DIR)/, binaries) \
			$(addprefix $(OBJS_DIR)/, ast) \
			$(addprefix $(OBJS_DIR)/, executer) \
			$(addprefix $(OBJS_DIR)/, parser)

LIBFT_NAME	= libft.a

LIBFT	= lib/libft/

SRCS_PATHS 	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_PATHS 	= $(addprefix $(OBJS_DIR)/, $(OBJS))

RM		= rm -rf

OS		:= $(shell uname -s)

LIB_LNK	= -L ${LIBFT}

INCLUDES = -I${LIBFT}inc -Iinc

all: ${NAME}

run: all
	./minishell

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@ 

$(NAME): ${LIBFT_NAME} ${OBJS_DIRS} ${OBJS_PATHS} 
	${CC} ${CFLAGS} ${LIB_LNK} ${OBJS_PATHS} -o ${NAME} -lft -lreadline

${LIBFT_NAME} :
	make -C ${LIBFT}
	cp ${LIBFT}/${LIBFT_NAME} .

$(OBJS_DIRS):
	@mkdir -p $(OBJS_DIRS) 2> /dev/null

clean:
		@${RM} *.a obj *.dSYM

fclean:		clean
		@${RM} ${NAME}

re:		fclean all

tags :
	ctags -R ${SRCS_PATHS}

.PHONY:	clean re fclean all
