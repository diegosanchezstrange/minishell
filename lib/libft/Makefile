NAME		= libft.a

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -c

SRCS_LIB	= ft_strlen.c ft_strlcat.c ft_strncmp.c ft_strlcpy.c ft_memset.c \
		  	ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_isalpha.c \
		  	ft_isalnum.c ft_isdigit.c ft_isprint.c ft_isascii.c \
		  	ft_memchr.c ft_memcmp.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c 

SRCS_LIB_B	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c \
		  	ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
		  	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

SRCS_PRINTF	= ft_printf.c ft_printf_string.c ft_printf_num.c ft_printf_hex.c 

SRCS_GNL 	= get_next_line.c get_next_line_utils.c

INC_PATH	= inc
SRCS_PATH	= src
OBJS_PATH	= objs

LIBFT_DIR 	= libft
PRINTF_DIR 	= printf
GNL_DIR 	= gnl

OBJS_DIRS	= $(addprefix $(OBJS_PATH)/, $(LIBFT_DIR)) \
			$(addprefix $(OBJS_PATH)/, $(PRINTF_DIR)) \
			$(addprefix $(OBJS_PATH)/, $(GNL_DIR))

SRCS_PATHS	= $(addprefix $(LIBFT_DIR)/, $(SRCS_LIB)) \
			$(addprefix $(LIBFT_DIR)/, $(SRCS_LIB_B)) \
			$(addprefix $(PRINTF_DIR)/, $(SRCS_PRINTF)) \
			$(addprefix $(GNL_DIR)/, $(SRCS_GNL))

OBJS_PATHS	= ${SRCS_PATHS:.c=.o}

SRCS		= $(addprefix $(SRCS_PATH)/, $(SRCS_PATHS))

OBJS		= $(addprefix $(OBJS_PATH)/, $(OBJS_PATHS))

RM			= rm -f

all: ${NAME}

${OBJS_PATH}/%.o: ${SRCS_PATH}/%.c | ${OBJS_DIRS}
	@${CC} ${CFLAGS} -D BUFFER_SIZE=32 $< -o $@ -I ${INC_PATH}

$(NAME) : ${OBJS} ${OBJS_DIRS} 
	@ar rc ${NAME} ${OBJS}

$(OBJS_DIRS):
	@mkdir -p $(OBJS_DIRS) 2> /dev/null

bonus : ${NAME} ${OBJS_B}
	@ar rc ${NAME} ${OBJS_B}

clean:
		@${RM} ${OBJS}

fclean:		clean
		@${RM} ${NAME}

re:		fclean all

.PHONY:	clean re fclean bonus all
