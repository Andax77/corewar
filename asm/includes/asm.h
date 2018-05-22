/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/22 17:07:37 by pmilan           ###   ########.fr       */
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

# define ERROR -1
# define SUCCESS 0

enum			e_list
{
	FINISHED, UNFINISHED, EMPTY, CHARACTER
};

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	t_list		*input;
	t_list		*instru;
	int			fd;
}				t_champ;

typedef struct	s_instru
{
	char		**params;
	char		*label_name;
	int			op_code;
	int			ocp;
	int			size;
	int			inst_addr;
}				t_instru;

void			ft_init_champ(t_champ *champ);
t_instru		*ft_init_instru(void);

int				read_file(char *file_name, t_champ *champ);
int				parse_line(char *line, t_champ *champ);

int				ft_check_params_type(t_instru *inst);
int				ft_check_params_format(t_instru *inst, char *str);

int				ft_get_instru(t_champ *champ);
int				ft_get_params(t_instru *inst, char *str);
int				ft_get_t_param(char *str);
int				ft_get_label_name(t_instru *inst, char *str);
int				ft_get_op_code(t_instru *inst, char *str);
int				ft_get_ocp(t_instru *inst);
void			ft_get_size_instruction(t_instru *inst);

void			ft_fill_lst_instru(t_champ *champ, t_instru *inst);
int				ft_fill_instru(t_instru *inst, char *str);
void			ft_fill_inst_addr(t_champ *champ);
void			ft_replace_direct(t_champ *champ);

int16_t			swap_int16(int16_t val);
int32_t			swap_int32(int32_t val);

void			ft_write_cor(t_champ *champ, char *name);
int				ft_fill_file_name(char *name, char **file_name);
int				ft_fill_output_params(t_instru *cur, char *output, int cursor);

void			ft_free_struct_instru(t_instru *inst);
void			del_champ(t_champ *champ);

void			ft_error(t_champ *champ, char *msg);
#endif
