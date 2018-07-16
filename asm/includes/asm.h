/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/16 15:58:49 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <op.h>
# include <libft.h>

# define BASE_HEXA "0123456789ABCDEF"
# define ERROR (-1)
# define SUCCESS (0)

enum			e_list
{
	FINISHED, UNFINISHED, EMPTY, CHARACTER
};

typedef struct	s_champ
{
	char		*argv;
	char		*file_name;
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

void			ft_init_champ(t_champ *champ, char *argv);
t_instru		*ft_init_instru(void);
int				ft_fill_file_name(t_champ *champ);
int				ft_fill_binary_name(t_champ *champ);

int				ft_verif_format_name(char *str);
int				ft_verif_format_comment(char *str);
int				ft_verif_register(t_champ *champ);
int				ft_name_comment_other_lines_next(char **member, char *tmp);

int				ft_parse_status(t_champ *champ, int status);
int				read_file(t_champ *champ);
int				read_binary(t_champ *champ);
int				ft_manual(t_champ *champ);

int				ft_check_input_format(t_champ *champ);
int				ft_check_params_type(t_instru *inst);
int				ft_check_params_format(t_instru *inst, char *str);
int				ft_empty_or_comment_line(char *str);
int				ft_check_champ_binary(t_champ **champ);

int				ft_get_instru(t_champ *champ);
int				ft_get_params(t_instru *inst, char *str);
int				ft_get_t_param(char *str);
void			ft_get_size_instruction(t_instru *inst);
int				ft_get_param_code(int num);
int				ft_decrypt_prog(t_champ *champ, unsigned char *prog,
		int inst_length);

void			ft_fill_lst_instru(t_champ *champ, t_instru *inst);
int				ft_fill_instru(t_instru *inst, char *str);
int				ft_fill_inst_addr_and_replace_direct(t_champ *champ);

int16_t			swap_int16(int16_t val);
int32_t			swap_int32(int32_t val);
int64_t			swap_int64(int64_t val);
char			*translate(int64_t val);
int				pad(char **str, int n);
unsigned char	*split_bits(char *prog);

int				ft_write_cor(t_champ *champ);
int				ft_fill_output_params(t_instru *cur, char *output, int cursor);
int				ft_write_s(t_champ *champ);

void			ft_free_struct_instru(t_instru *inst);
int				del_champ(t_champ *champ);

int				ft_error(t_champ *champ, char *msg);
int				ft_error_m(t_champ *champ, char *msg);
#endif
