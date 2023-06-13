# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-has <svan-has@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/30 07:53:48 by svan-has      #+#    #+#                  #
#    Updated: 2023/05/06 13:54:05 by svan-has      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Werror -Wextra
NAME := libftprintf.a
SRC_DIR := src
OBJ_DIR := obj
SRC := \
	ft_printf.c \
	ft_putchar_return.c \
	ft_putstr_return.c \
	ft_putnbr_plus.c \
	ft_isalpha.c
SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re