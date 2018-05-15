/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/15 13:42:05 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "GNL/get_next_line.h"
#include "ft_printf/srcs/ft_printf.h"

typedef struct s_champ
{
	char		*name;
	char		*comment;
	t_list		*instru;
}				t_champ;

typedef struct	s_instru
{
	char		*label;
	int			op_code;
	int			ocp;
	char		*params;
}				t_instru;
