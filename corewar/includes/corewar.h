/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/31 17:24:39 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <libft.h>
# include <ncurses.h>
# include <op.h>

enum				e_list
{
	FINISHED, UNFINISHED, ERROR, SUCCESS
};

typedef struct		s_opt
{
	int				a;
	int				d;
	int				s;
	int				v;
	int				b;
	int				bs;
	int				n;
	int				ns;
}					t_opt;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	char			*prog;
	unsigned char	*splited_prog;
	t_list			*instru;
	int				size;
	int				op_nb;
	int				pc;
	int				carry;
}					t_champ;

typedef struct		s_cor
{
	t_opt			*opt;
	t_list			*champs;
	char			*map;
	int				cycles;
}					t_cor;

void				print_usage(void);
int					is_opt(char *str);
int					parse_opt(char **argv, t_opt *opt, t_cor *cor);
int					init(char **argv, t_cor *cor);
int					init_ncurses(t_opt *opt);
int					init_cor(t_cor *cor, char **argv);
int					check_champ(t_champ **champ, char *path);
int64_t				swap_int(int64_t c);
char				*translate(int64_t val);
int					pad(char **str, int n);
void				split_bits(char **prog, unsigned char **splited_prog);
void				del_champ(void *content, size_t content_size);
void				del(void *content, size_t content_size);

#endif
