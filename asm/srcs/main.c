/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 20:07:51 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/24 22:31:48 by pmilan           ###   ########.fr       */
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
			champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
			ft_init_champ(champ, argv[argc]);
			if (ft_fill_file_name(champ, argv[argc]) == ERROR)
				continue ;
			if (read_file(argv[argc], champ) == ERROR)
				continue;
			ft_write_cor(champ);
			del_champ(champ);
		}
	}
	if (argc_c == 1)
		ft_printf("{yellow}Usage: %s <sourcefile.s>{eoc}\n", argv[0]);
	exit(EXIT_SUCCESS);
}
