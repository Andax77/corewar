/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:36:59 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/29 18:02:28 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			read_binary(char *path, t_champ *champ)
{
	uint64_t	c;
	int			ret;

	if (ft_fill_binary_name(champ, path) == ERROR)
		return (ERROR);
	if ((champ->fd = open(path, O_RDONLY)) <= 0)
		return (ERROR);
	while ((ret = read(fd, &c, 4)))

	return (SUCCESS);
}
