/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/18 18:25:25 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <op.h>
#include <libft.h>

enum			e_list
{
	FINISHED, UNFINISHED, ERROR, SUCCESS, EMPTY, CHARACTER
};

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	t_list		*input;
//	t_list		*label;
	t_list		*instru;
	int			fd;
}				t_champ;

//typedef struct	s_label
//{
//	char		*label_name;
//	int			label_addr;
//}				t_label;
//
typedef struct	s_instru
{
	char		**params;
	char		*label_name;
	int			op_code;
	int			ocp;
	int			size;
	int			label_addr;
}				t_instru;

void			ft_init_champ(t_champ *champ);
t_instru		*ft_init_instru(void);

int				read_file(char *file_name, t_champ *champ);
int				parse_line(char *line, t_champ *champ);
int				ft_get_instru(t_champ *champ);

void			del_champ(t_champ *champ);

#endif
