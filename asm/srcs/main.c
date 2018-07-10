/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 20:07:51 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/09 19:34:23 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		main_reverse(t_champ *champ)
{
	if (read_binary(champ) == ERROR)
		return (ERROR);
	if (ft_write_s(champ) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int		main_normal(t_champ *champ)
{
	if (ft_fill_file_name(champ) == ERROR)
		return (ERROR);
	if (read_file(champ) == ERROR)
		return (ERROR);
	if (ft_write_cor(champ) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static void		main_loop(t_champ *champ, int argc_c, char **argv)
{
	while (--argc_c)
	{
		champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
		ft_init_champ(champ, argv[argc_c]);
		if (ft_strcmp("-r", argv[1]) == 0)
		{
			if (argc_c == 1 && del_champ(champ))
				break ;
			if (main_reverse(champ) == ERROR)
				continue ;
		}
		else if (ft_strcmp("-m", argv[1]) == 0)
		{
			ft_manual(champ);
			break ;
		}
		else
		{
			if (main_normal(champ) == ERROR)
				continue ;
		}
		del_champ(champ);
	}
}

int				main(int argc, char **argv)
{
	t_champ		*champ;
	int			argc_c;

	argc_c = argc;
	champ = NULL;
	if (MAX_ARGS_NUMBER != 4)
	{
		ft_printf("{red}stop touching op.h !\n{eoc}");
		exit(EXIT_FAILURE);
	}
	main_loop(champ, argc_c, argv);
	if (argc == 1)
		ft_printf("{yellow}Usage: %s [-rm] <sourcefile> ...{eoc}\n\
*****************************************************************\n\
*	normal mode (compiles a .s in .cor)			*\n\
*  -r : reverse mode (compiles a .cor in .s)			*\n\
*  -m : manual mode (opens a manual mode to create a .cor)	*\n\
*****************************************************************\n", argv[0]);
	exit(EXIT_SUCCESS);
}
