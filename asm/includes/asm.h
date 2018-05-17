/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/17 15:15:04 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

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
