/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:57:35 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/17 15:05:33 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	while (*alst && (*del))
	{
		ft_lstdel(&(*alst)->next, (*del));
		ft_lstdelone(alst, (*del));
	}
}
