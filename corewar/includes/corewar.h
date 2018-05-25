/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/25 23:59:48 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ncurses.h>
#include <op.h>

enum			e_list
{
	FINISHED, UNFINISHED, ERROR, SUCCESS
};

typedef struct	s_opt
{
	int			a;
	int			d;
	int			s;
	int			v;
	int			b;
	int			bs;
	int			n;
	int			ns;
}				t_opt;

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	t_list		*instru;
}				t_champ;

typedef struct	s_cor
{
	t_opt		*opt;
	t_list		*champs;
	char		*map;
	int			pc;
	int			carry;
	int			cycles;
}				t_cor;

void	print_usage(void);
int		is_opt(char *str);
int		parse_opt(char **argv, t_opt *opt, t_cor *cor);
int		init(char **argv, t_cor *cor);
int		init_ncurses(t_opt *opt);
int		init_cor(t_cor *cor, char **argv);
int		check_champ(t_champ **champ, char *path);
void	del_champ(void *content, size_t content_size);
void	del(void *content, size_t content_size);
