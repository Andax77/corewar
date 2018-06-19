/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:59:35 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/17 15:06:55 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

int		ft_lstmax(t_list *lst)
{
	int	max;

	max = INT_MIN;
	while (lst && lst->content)
	{
		if (((*(int*)lst->content) > max))
			max = (*(int*)lst->content);
		lst = lst->next;
	}
	return (max);
}
