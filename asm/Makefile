# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmilan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:16:13 by pmilan            #+#    #+#              #
#    Updated: 2018/06/10 20:07:08 by pmilan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FILES = main.c \
		ft_init.c \
		ft_parsing.c \
		ft_parsing_binary.c \
		ft_fill_instru.c \
		ft_fill_instru_annexe.c \
		ft_get_instru.c \
		ft_decrypt_prog.c \
		ft_check.c \
		ft_check_binary.c \
		ft_replace.c \
		ft_endian.c \
		ft_asm_tools.c \
		ft_write_cor.c \
		ft_write_cor_annexe.c \
		ft_del.c \
		ft_error.c \
		../../commun/srcs/op.c

HFILES = includes/asm.h \
		 ../commun/includes/op.h \
		 $(LIBFT_DIR)includes/libft.h

LIBFT_DIR = ../libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_LIB = -L $(LIBFT_DIR) -lft

CC = gcc
CFLAGS = -Wall -Wextra -g#-Werror -O3

OBJ_DIR = objs/
SRCS_DIR = srcs/

INC_DIR = includes/ \
		  ../commun/includes/ \
		  $(LIBFT_DIR)includes/

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
	@make -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)"
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@printf $(CYAN)"-> compilation : $(NAME)\n"$(NORMAL)
	@$(CC) -o $(NAME) $(OBJ) $(INC) $(CFLAGS) $(LIBFT_LIB)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HFILES)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CC) -c $(INC) $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	@mkdir -p $(dir $(OBJ))

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
