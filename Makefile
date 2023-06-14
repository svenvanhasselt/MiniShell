# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-has <svan-has@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/31 19:05:22 by svan-has      #+#    #+#                  #
#    Updated: 2023/05/26 15:11:57 by svan-has      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := fdf
CC := cc
CFLAGS := -Werror -Wall -Wextra
LIBMLX	:= ./library/MLX42
LIBFT	:= ./library/libft
HEADERS := -I lib/include -I $(LIBMLX)/include -I $(LIBFT)/includes -I include
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/libmlx42.a $(LIBMLX)/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm
SRC_DIR := source
OBJ_DIR := object
SRC := \
		rendering.c \
		tools.c \
		drawing.c \
		calculating.c \
		mouse.c \
		parsing.c \
		iso_rotation.c \
		keys.c \
		errors.c \
		color.c \
		main.c

SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM := rm -rf

all: libft libmlx $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)
	$(info FDF Compiled)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBMLX) clean
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all libft libmlx clean fclean