# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmilan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/04 13:09:25 by pmilan            #+#    #+#              #
#    Updated: 2018/05/26 00:56:02 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_strlen.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_is_int.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_itoa_base.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_strdup.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlcat.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstget.c \
		ft_lstaddend.c \
		ft_lstsort.c \
		ft_lstcount.c \
		ft_lstmax.c \
		ft_lstmin.c \
		ft_realloc.c \
		ft_read_fd.c \
		ft_read_file.c \
		ft_int_to_base.c \
		ft_int_to_nbase.c \
		ft_base_to_int.c \
		ft_convert_base.c \
		ft_ftoa.c \
		ft_ltoa.c \
		ft_lltoa.c \
		ft_abs.c \
		ft_strndup.c \
		ft_power.c \
		ft_2arg.c \
		ft_get2arg.c \
		ft_islower.c \
		ft_isupper.c \
		ft_atoi_base.c \
		ft_str_toupper.c \
		ft_strisdigit.c \
		ft_two_swap.c \
		ft_number_len.c \
		ft_malloc.c \
		ft_fruit.c \
		ft_bzstrcpy.c \
		ft_total_tab.c \
		ft_init_tab.c \
		ft_sqrt.c \
		ft_smallest.c \
		ft_biggest.c \
		ft_str_and_free_join.c \
		get_next_line.c \
		ft_printf/printf/ft_printf.c \
		ft_printf/printf/ft_vprintf.c \
		ft_printf/printf/ft_dprintf.c \
		ft_printf/printf/ft_vdprintf.c \
		ft_printf/printf/ft_asprintf.c \
		ft_printf/printf/ft_vasprintf.c \
		ft_printf/printf/ft_errprintf.c \
		ft_printf/color/ft_color.c \
		ft_printf/color/ft_init_color.c \
		ft_printf/check/ft_parse.c \
		ft_printf/check/ft_check.c \
		ft_printf/check/ft_initarg.c \
		ft_printf/check/ft_forest.c \
		ft_printf/check/ft_checkconv.c \
		ft_printf/check/ft_cleanstars.c \
		ft_printf/check/ft_cleanstars2.c \
		ft_printf/conv/ft_wchart.c \
		ft_printf/conv/ft_wchart_2.c \
		ft_printf/conv/ft_getheight.c \
		ft_printf/conv/ft_precision_e.c \
		ft_printf/conv/ft_precision_e_2.c \
		ft_printf/conv/ft_conv_bigs.c \
		ft_printf/conv/ft_conv_bigs_2.c \
		ft_printf/conv/ft_conv_s.c \
		ft_printf/conv/ft_fill_str_ud.c \
		ft_printf/conv/ft_conv_d.c \
		ft_printf/conv/ft_conv_o.c \
		ft_printf/conv/ft_conv_u.c \
		ft_printf/conv/ft_conv_x.c \
		ft_printf/conv/ft_conv_c.c \
		ft_printf/conv/ft_conv_k.c \
		ft_printf/conv/ft_conv_n.c \
		ft_printf/conv/ft_conv_b.c \
		ft_printf/conv/ft_conv_w.c \
		ft_printf/conv/ft_conv_f.c \
		ft_printf/conv/ft_flags_f.c \
		ft_printf/conv/ft_arrondis_f.c \
		ft_printf/conv/ft_conv_e.c \
		ft_printf/conv/ft_conv_g.c \
		ft_printf/conv/ft_conv_g_annexe.c \
		ft_printf/conv/ft_conv_r.c \
		ft_printf/conv/ft_conv_modulo.c \
		ft_printf/conv/ft_conv_invalid.c \
		ft_printf/conv/ft_regle_zero.c \
		ft_printf/ft_strfreejoin.c

HFILES = includes/ft_printf.h \
		 includes/ft_printf_2.h \
		 includes/ft_printf_struct.h \
		 includes/libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

INC_DIR = includes/
SRCS_DIR = srcs/
OBJS_DIR = objs/

INC := $(addprefix -I , $(INC_DIR))
SRCS := $(addprefix $(SRCS_DIR), $(FILES))
OBJS := $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"

START = @printf $(GREEN)"LIBFT\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)"--------------------\n"$(NORMAL)

all:
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJS_DIR) $(OBJS)
	@printf $(CYAN)"-> create lib : $(NAME)\n"$(NORMAL)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HFILES)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CC) -c $(INC) $< -o $@ $(CFLAGS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(dir $(OBJS))

clean:
	$(START)
	@printf $(RED)"-x remove .o files\n"$(NORMAL)
	@rm -rf $(OBJS_DIR)
	$(END)

cleanlib:
	$(START)
	@printf $(RED)"-x remove $(NAME)\n"$(NORMAL)
	@rm -f $(NAME)
	$(END)

fclean: clean cleanlib

re: fclean
	@make

exec:
	@clear
	@make all
	@$(CC) ../main.c -lmlx -framework OpenGL -framework AppKit -o ../fdf $(INC) -L . $(CFLAGS) -lft
	@printf $(MAGENTA)"FDF\n--------------------\n"$(NORMAL)
	@../fdf
	@printf $(MAGENTA)"--------------------\n"$(NORMAL)

.PHONY: all clean fclean re exec
