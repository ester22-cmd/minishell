# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:19:13 by amaferre          #+#    #+#              #
#    Updated: 2025/02/10 19:20:35 by amaferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_strncmp.c ft_memcmp.c ft_isalnum.c ft_isascii.c ft_strnstr.c \
	ft_strdup.c ft_memcpy.c ft_calloc.c ft_isprint.c ft_strlen.c ft_isalpha.c \
	ft_strlcat.c ft_memset.c ft_bzero.c ft_strlcpy.c ft_memchr.c ft_isdigit.c \
	ft_strchr.c ft_memmove.c ft_toupper.c ft_strrchr.c ft_atoi.c ft_tolower.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_split.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

HEADER = -I .

OBJECTS = ${SRCS:.c=.o}

%.o: %.c
	${CC} ${CFLAGS} ${HEADER} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

clean:
	rm -rf ${OBJECTS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean all fclean re
 