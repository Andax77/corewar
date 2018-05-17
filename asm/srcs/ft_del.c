/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:18:42 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/17 19:40:01 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	del_input(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

//static void	del_instru(void *content, size_t content_size)
//{
	//TODO
//}
//

void		del_champ(t_champ *champ)
{
	free(champ->name);
	free(champ->comment);
	ft_lstdel(&champ->input, del_input);
	free(champ);
}
