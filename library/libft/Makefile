# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-has <svan-has@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/06 12:06:15 by svan-has      #+#    #+#                  #
#    Updated: 2023/05/26 15:10:36 by svan-has      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = libft.a
SRC_DIR := source
INC_DIR := includes
GNL_DIR := gnl
FT_PRINTF := source/ft_printf
OBJ_DIR := object
CFLAGS := -I $(INC_DIR) -I $(GNL_DIR) -Wall -Wextra -Werror
SRC := ft_atoi.c ft_bzero.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strjoin_free.c ft_strtrim_free.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c ft_substr_free.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_count_word.c ft_count_items.c ft_split_num.c ft_atoi_li.c
SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM = rm -rf

all: ft_printf $(NAME)

ft_printf:
	@$(MAKE) -C $(FT_PRINTF)

$(NAME): $(OBJ)
	@cp $(FT_PRINTF)/libftprintf.a ./
	@mv libftprintf.a libft.a
	@ar -rc $(NAME) $(OBJ)
	$(info Libft Compiled)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(FT_PRINTF) fclean

fclean: clean
	@$(RM) $(NAME)

re:	 fclean all

.PHONY: clean

