# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 19:40:33 by eparisot          #+#    #+#              #
#    Updated: 2018/03/08 21:06:09 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

SRCS	=	libftprintf/ft_putchar.c \
			libftprintf/ft_putchar_w.c \
			libftprintf/ft_putnbr.c \
			libftprintf/ft_putnbr_oct_l.c \
			libftprintf/ft_putnbr_hex_l.c \
			libftprintf/ft_putnbr_hex_up_l.c \
			libftprintf/ft_putnbr_hex_p.c \
			libftprintf/ft_putnbr_unsigned_l.c \
			libftprintf/ft_putstr.c \
			libftprintf/ft_putstr_w.c \
			libftprintf/ft_strdup.c \
			libftprintf/ft_strlen.c \
			libftprintf/ft_strlen_w.c \
			libftprintf/ft_strcpy.c \
			libftprintf/ft_strchr.c \
			libftprintf/ft_memalloc.c \
			libftprintf/ft_strnew.c \
			libftprintf/ft_pw.c \
			libftprintf/ft_atoi.c \
			libftprintf/ft_isdigit.c \
			libftprintf/ft_countdigits.c \
			libftprintf/ft_countdigits_hex.c \
			libftprintf/ft_countdigits_oct.c \
			libftprintf/ft_countdigits_u.c \
			libftprintf/ft_wcharlen.c \
			srcs/ft_printf.c \
			srcs/if_forest.c\
			srcs/parse_c.c\
			srcs/parse_di.c\
			srcs/parse_flags.c\
			srcs/parse_lld.c\
			srcs/parse_llo.c\
			srcs/parse_lls.c\
			srcs/parse_llu.c\
			srcs/parse_llx.c\
			srcs/parse_o.c\
			srcs/parse_p.c\
			srcs/parse_s.c\
			srcs/parse_u.c\
			srcs/parse_x.c

OBJS	=	$(SRCS:.c=.o)

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

$(NAME)	:	$(OBJS)
	ar rc $(NAME) $(OBJS)

all		:	$(NAME)

clean	:
	$(RM) $(OBJS)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all
