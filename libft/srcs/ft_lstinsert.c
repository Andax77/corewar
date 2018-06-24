/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:08:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/24 14:44:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libft.h>

void	ft_lstinsert(t_list **lst, t_list *new, int i)
{
	t_list	*tmp;
	t_list	*next;
	int		j;

	j = 0;
	tmp = *lst;
	if (*lst && new && i > 0 && i < (int)ft_lstcount(*lst))
	{
		while ((*lst)->next && j++ < i)
			*lst = (*lst)->next;
		next = (*lst)->next;
		(*lst)->next = new;
		new->next = next;
		*lst = tmp;
	}
	else if (*lst && new && i == 0)
		ft_lstadd(lst, new);
	else if (*lst && new && i == (int)ft_lstcount(*lst))
		ft_lstaddend(lst, new);
}
