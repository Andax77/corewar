/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:59:35 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/17 15:07:10 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

int		ft_lstmin(t_list *lst)
{
	int	min;

	min = INT_MAX;
	while (lst && lst->content)
	{
		if (((*(int*)lst->content) < min))
			min = (*(int*)lst->content);
		lst = lst->next;
	}
	return (min);
}
