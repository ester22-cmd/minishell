NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIB_DIR = lib

SRCS = $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)