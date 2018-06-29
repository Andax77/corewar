/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/29 18:36:47 by eparisot         ###   ########.fr       */
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
	int				*n;
	int				a;
	int				d;
	int				v;
}					t_opt;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	char			*prog;
	unsigned char	*splited_prog;
	unsigned int	*reg;
	t_list			*instru;
	int				id;
	int				v_id;
	int				op_nb;
	int				pc;
	int				last_pc;
	int				carry;
	int				r_cy;
	int				lives;
	int				v_lives;
	int				last_live;
	int				last_live_pc;
	int				last_st_pc;
	int				last_st;
	int				live;
	int				father;
}					t_champ;

typedef struct		s_cor
{
	t_opt			*opt;
	t_list			*champs;
	unsigned char	*map;
	short			*c_map;
	char			*aff;
	int				cycle;
	int				cycle_to_die;
	int				v_cycle;
	int				checks;
	int				winner;
}					t_cor;

void				print_usage(void);
int					is_opt(char *str);
int					parse_opt(char **argv, t_opt *opt, t_cor *cor);
void				init_opt(t_opt *opt, t_cor *cor);
int					check_opt(char **argv);
void				verif_doublons(t_opt *opt, int index);
int					is_opt(char *str);
void				print_usage(void);
int					init(char **argv, t_cor *cor);
int					count_champs(t_list *champs);
void				init_op(void (**f)(t_cor*, t_champ*));
int					recup_content(t_cor *cor, t_champ *champ, int ocp, int decalage, int op_code);
void				draw_uchar(int pos, unsigned char val);
void				draw_line(int line_idx, int col_idx, char *line);
void				draw_names(t_list *champs);
int					init_ncurses(t_cor *cor);
void				draw_borders(void);
void				draw_map(t_cor *cor);
void				draw_infos(t_list *champs, int nb);
void				init_colors(t_list *champs);
void				init_special_colors(void);
void				init_cmap(t_cor *cor);
int					init_cor(t_cor *cor, char **argv);
int					check_champ(t_champ **champ, char *path, int nb);
int64_t				swap_int(int64_t c);
char				*translate(int64_t val);
int					pad(char **str, int n);
void				split_bits(char **prog, unsigned char **splited_prog);
int					check_op_len(t_champ *t_champ);
void				order_to_start(t_list **champs);
void				cycle(t_cor *cor, int ret);
void				clean(t_cor *cor, t_list *champs);
void				cycle_job(t_cor *cor, t_champ *cur_champ);
int					check_lives(t_cor *cor);
void				print_infos(t_cor *cor);
void				key_event(int *timeout, int *ch);
int					*key_handler(int *timeout, int *ch);
int					change_r_cy(t_cor *cor, t_champ *champ);
int					check_live_value(t_cor *cor, int pc);
void				dump(t_cor *cor);
void				jump(t_cor *cor);
void				del_champ(void *content, size_t content_size);
void				del(void *content, size_t content_size);

/*
COW ART
*/
void				draw_line2(int line_idx, char *line);
void				draw_cow1(int nb);
void				draw_cow2(int nb);
void				draw_cow3(int nb);
void				print_cow();

/*
HEART BEAT
*/
void				print_player(int player);
void				print_heart(t_cor *cor);
void				print_heart2(int player, int stat);
void				draw_heart(int line_idx, int y, char *line, int i);
void				stat1(int player);
void				stat2(int player);
void				stat3(int player);
void				stat4(int player);
void				draw_player(int line_idx, int y, char *line);
void				draw_player_id(int line_idx, int y, char *line);
void				player(int player);
void				draw_player(int line_idx, int y, char *line);
void				heart_color();
int					stat_heart(t_cor *cor, t_list *champs);
void				get_color_heart(int live, char *line, int id);

/*
CYCLE FCT
*/
void				ft_move(t_cor *cor, t_champ *champ);
void				ft_live(t_cor *cor, t_champ *champ);
void				ft_ld(t_cor *cor, t_champ *champ);
void				ft_st(t_cor *cor, t_champ *champ);
void				ft_add(t_cor *cor, t_champ *champ);
void				ft_sub(t_cor *cor, t_champ *champ);
void				ft_and(t_cor *cor, t_champ *champ);
void				ft_or(t_cor *cor, t_champ *champ);
void				ft_xor(t_cor *cor, t_champ *champ);
void				ft_zjmp(t_cor *cor, t_champ *champ);
void				ft_ldi(t_cor *cor, t_champ *champ);
void				ft_sti(t_cor *cor, t_champ *champ);
void				ft_fork(t_cor *cor, t_champ *champ);
void				legacy(t_cor *cor, t_champ *champ, int id, int pc);
void				ft_lld(t_cor *cor, t_champ *champ);
void				ft_lldi(t_cor *cor, t_champ *champ);
void				ft_lfork(t_cor *cor, t_champ *champ);
void				ft_aff(t_cor *cor, t_champ *champ);

/*
PRINT WINNER
*/
void				print_intro(t_cor *cor);
char				*get_name_champ(t_cor *cor);
char				*color_player(int id);

#endif
