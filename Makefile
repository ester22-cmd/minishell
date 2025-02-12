NAME =		minishell
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
SRC_DIR    := src
OBJ_DIR    := obj
RM = rm -rf

LIBFT_DIR = ./LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES =	main.c \
			crud_list.c \
			crud_env.c \
			free.c \
			init.c \
			miniexit.c \
			split_cmd.c \
			builtin.c \
			sanitizer.c \
			miniexport.c \
			minicd.c \
			miniecho.c \
			minienv.c \
			miniunset.c \
			minipwd.c \
			redir.c \
			run.c \
			get_cmd.c \
			input.c \
			verify.c \
			find_path_utils.c \
			find_path.c \
			dollar.c \
			signals.c \
			get_cmd_utils.c \
			dollar_utils.c \
			run_utils.c

SRC =		$(addprefix src/, $(SRC_FILES))

OBJECTS =	$(SRC:.c=.o)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJECTS) include/minishell.h
			$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

clean:
		rm -rf $(obj)
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJECTS)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libft