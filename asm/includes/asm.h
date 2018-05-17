/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/17 19:38:36 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

enum			e_list
{
	FINISHED, UNFINISHED, ERROR, SUCCESS
};

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	t_list		*input;
//	t_list		*instru;
	int			fd;
}				t_champ;

typedef struct	s_instru
{
	char		**params;
	char		*label;
	int			addr_label;
	int			op_code;
	int			ocp;
}				t_instru;

void			ft_init(t_champ *champ);

int				read_file(char *file_name, t_champ *champ);
int				parse_line(char *line, t_champ *champ);

void			del_champ(t_champ *champ);
