/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 20:07:51 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/18 18:15:34 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		main(int argc, char **argv)
{
	t_champ		*champ;

	if (argc > 1)
	{
		if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
			return (0);
		ft_init_champ(champ);
		if (read_file(argv[1], champ) == ERROR)
		{
			del_champ(champ);
			exit(EXIT_FAILURE);
		}
		ft_write_cor(champ, argv[1]);
		del_champ(champ);
	}
	else
		ft_printf("{yellow}Usage: %s <sourcefile.s>{eoc}\n", argv[0]);
	exit(EXIT_SUCCESS);
}
