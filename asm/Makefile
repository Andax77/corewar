# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmilan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:16:13 by pmilan            #+#    #+#              #
#    Updated: 2018/05/17 19:38:45 by pmilan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FILES = main.c \
		ft_init.c \
		ft_read_file.c \
		ft_parsing.c \
		ft_del.c \


HFILES = includes/asm.h

CC = gcc
CFLAGS = -Wall -Wextra -g#-Werror -O3

INC_DIR = includes/ \
		  $(LIBFT_DIR)includes

SRCS_DIR = srcs/
OBJ_DIR = objs/

LIBFT_DIR = ../libft/
LIBFT_LIB = -L $(LIBFT_DIR) -lft

INC := $(addprefix -I, $(INC_DIR))
SRCS := $(addprefix $(SRCS_DIR), $(FILES))
OBJ := $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"

START = @printf $(GREEN)"ASM\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)"--------------------\n"$(NORMAL)

all:
	@make -C $(LIBFT_DIR)
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT_DIR)libft.a
	@printf $(CYAN)"-> compilation : $(NAME)\n"$(NORMAL)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFT_LIB)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HFILES)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CC) -c $(INC) $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJ))

$(LIBFT_DIR)libft.a:
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	$(START)
	@printf $(RED)"-x remove .o files\n"$(NORMAL)
	@rm -rf $(OBJ_DIR)
	$(END)

fclean: clean
	@make -C $(LIBFT_DIR) cleanlib
	$(START)
	@printf $(RED)"-x remove $(NAME)\n"$(NORMAL)
	@rm -f $(NAME)
	$(END)

re: fclean
	@make

.PHONY: all clean fclean re
