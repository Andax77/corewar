/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:36:59 by pmilan            #+#    #+#             */
/*   Updated: 2018/06/09 16:15:12 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	ft_populate_input(t_champ **champ, int64_t c)
{
	t_list		**input;
	char		*tmp;
	t_list		*new;

	input = &(*champ)->input;
	if (!(tmp = ft_itoa(swap_int64(c))))
		exit(EXIT_FAILURE);
	if (!*input)
	{
		if (!(*input = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(new = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			exit(EXIT_FAILURE);
		ft_lstaddend(input, new);
	}
	free(tmp);
}

int			read_binary(t_champ *champ)
{
	int64_t		c;
	int			ret;

	if (ft_fill_binary_name(champ) == ERROR)
		return (ERROR);
	if ((champ->fd = open(champ->argv, O_RDONLY)) <= 0)
		return (ft_error(champ, "error: bad file descriptor"));
	while ((ret = read(champ->fd, &c, 4)))
		ft_populate_input(&champ, c);
	close(champ->fd);
	if (ft_check_champ_binary(&champ) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
