# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmilan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:16:13 by pmilan            #+#    #+#              #
#    Updated: 2018/06/14 09:06:43 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

FILES = main.c \
		parse_opt.c \
		init.c \
		init_cor.c \
		parse_champ.c \
		tools.c \
		parse_op.c \
		../../commun/srcs/op.c \
		cycle.c \
		#op1.c \
		op2.c \
		op3.c \

HFILES = includes/corewar.h \
		 ../commun/includes/op.h \
		 $(LIBFT_DIR)includes/libft.h

CC = gcc
CFLAGS = -Wall -Wextra -g#-Werror -O3

INC_DIR = includes/ \
		  ../commun/includes/ \
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

START = @printf $(GREEN)"COREWAR\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)"--------------------\n"$(NORMAL)

all:
	@make -C $(LIBFT_DIR)
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT_DIR)libft.a
	@printf $(CYAN)"-> compilation : $(NAME)\n"$(NORMAL)
	@$(CC) -lncurses -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFT_LIB)

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
