/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 20:07:51 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/23 12:09:56 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		main(int argc, char **argv)
{
	t_champ		*champ;
	int			argc_c;

	argc_c = argc;
	while (--argc)
	{
		if (!ft_strequ(argv[argc], "-r"))
		{
			if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
				return (0);
			ft_init_champ(champ);
			if (read_file(argv[argc], champ) == ERROR)
			{
				del_champ(champ);
				ft_printf("{red}error: '%s' {red}is not a valid file{eoc}\n", \
				argv[argc]);
				continue;
			}
			ft_write_cor(champ, argv[argc]);
			del_champ(champ);
		}
	}
	if (argc_c == 1)
		ft_printf("{yellow}Usage: %s <sourcefile.s>{eoc}\n", argv[0]);
	exit(EXIT_SUCCESS);
}
