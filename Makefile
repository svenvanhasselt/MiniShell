# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sven <sven@student.42.fr>                    +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/31 19:05:22 by svan-has      #+#    #+#                  #
#    Updated: 2023/08/21 18:22:48 by psadeghi      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


READLINEFLAGS += -lreadline -L $(shell brew --prefix readline)/lib

NAME := minishell
CC := cc
CFLAGS := #-Wall -Werror -Wextra #-g -fsanitize=address
LIBFT	:= ./library/libft
#MINISHELL	:= ./minishell.a
HEADERS := -I $(LIBFT)/includes -I includes -I $(shell brew --prefix readline)/include
LIB	:= $(LIBFT)/libft.a
SRC_DIR := source
OBJ_DIR := object
SRC := \
		main.c\
		lexer/lexer.c\
		lexer/ll_lexer.c\
		expansion/expansion.c\
		expansion/utils.c\
		parser/parser.c\
		parser/ll_list_parser.c\
		parser/ll_node_parser.c\
		syntax/syntax_error.c\
		syntax/qoute_managing.c\
		syntax/token_comb.c\
		redirection/rd.c\
		redirection/rd_atfirst.c\
		redirection/rd_atfirst_utils.c\
		redirection/rd_heredoc.c\
		execution/execution.c\
		execution/utils.c\
		execution/init.c\
		execution/error_handling.c\
		execution/redirection.c\
		builtins/echo.c\
		builtins/cd.c\
		builtins/pwd.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/export.c\
		builtins/exit.c\
		signals/signals.c\
		
SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM := rm -rf

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(HEADERS) -o $(NAME) $(READLINEFLAGS)
	$(info minishell Compiled)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS) 

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all libft clean fclean