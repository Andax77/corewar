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

int		main(int ac, char **av)
{
	t_champ		*champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (0);
	ft_init_champ(champ);
	if (ac > 1 && read_file(av[1], champ) == ERROR)
	{
		del_champ(champ);
		exit(EXIT_FAILURE);
	}
	del_champ(champ);
	exit(EXIT_SUCCESS);
}
