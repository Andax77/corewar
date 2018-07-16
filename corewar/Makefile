# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmilan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:16:13 by pmilan            #+#    #+#              #
#    Updated: 2018/07/16 16:16:09 by pmilan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

FILES = main.c \
		parse_opt.c \
		parse_opt2.c \
		init.c \
		init_ncurses.c \
		init_ncurses2.c \
		init_cor.c \
		parse_champ.c \
		parse_champ2.c \
		tools.c \
		tools2.c \
		legacy.c \
		parse_op.c \
		../../commun/srcs/op.c \
		key_handling.c \
		key_handling2.c \
		cycle.c \
		cycle2.c \
		cycle3.c \
		exec_op.c \
		op_move_add_sub_aff.c \
		op_ld_st.c \
		op_and_or_xor.c \
		op_sti.c \
		op_ldi_lld_lldi.c \
		op_zjmp_fork_lfork.c \
		op_live.c \
		player.c \
		cow.c \
		heart.c \
		heart2.c \
		print.c \
		winner.c

HFILES = includes/corewar.h \
		 ../commun/includes/op.h \
		 $(LIBFT_DIR)includes/libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
	@rm -rf ../commun/srcs/op.o
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
