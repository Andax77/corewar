/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 20:07:51 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/29 17:26:38 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int				main(int argc, char **argv)
{
	t_champ		*champ;
	int			argc_c;

	argc_c = argc;
	while (--argc_c)
	{
		champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
		ft_init_champ(champ, argv[argc_c]);
		if (ft_strcmp("-r", argv[1]) == 0)
		{
			if (argc_c == 1)
				continue ;

		}
		else
		{
			if (ft_fill_file_name(champ, argv[argc_c]) == ERROR)
				continue ;
			if (read_file(argv[argc_c], champ) == ERROR)
				continue ;
			if (ft_write_cor(champ) == ERROR)
				continue ;
		}
		del_champ(champ);
	}
	if (argc == 1)
		ft_printf("{yellow}Usage: %s [-r] <sourcefile> ...{eoc}\n", argv[0]);
	exit(EXIT_SUCCESS);
}
