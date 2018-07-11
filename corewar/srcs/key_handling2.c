/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/11 16:28:00 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int	*key_event_e(int *timeout)
{
	char	*p_p_c;

	if (!(p_p_c = ft_itoa(1000 - --*timeout)))
		exit(EXIT_FAILURE);
	attron(COLOR_PAIR(17));
	draw_line(4, 22, "    ");
	draw_line(4, 22, p_p_c);
	free(p_p_c);
	return (timeout);
}

static int	*key_event_r(int *timeout)
{
	char	*p_p_c;

	if (1000 - (*timeout - 10) > 1000)
	{
		if (!(p_p_c = ft_itoa(1000
						- (*timeout = 0))))
			exit(EXIT_FAILURE);
	}
	else if (!(p_p_c = ft_itoa(1000
					- (*timeout -= 10))))
		exit(EXIT_FAILURE);
	attron(COLOR_PAIR(17));
	draw_line(4, 22, "    ");
	draw_line(4, 22, p_p_c);
	free(p_p_c);
	return (timeout);
}

static int	*key_event_w(int *timeout)
{
	char	*p_p_c;

	if (!(p_p_c = ft_itoa(1000 - ++*timeout)))
		exit(EXIT_FAILURE);
	attron(COLOR_PAIR(17));
	draw_line(4, 22, "    ");
	draw_line(4, 22, p_p_c);
	free(p_p_c);
	return (timeout);
}

static int	*key_event_q(int *timeout)
{
	char	*p_p_c;

	if (1000 - (*timeout + 10) < 50)
	{
		if (!(p_p_c = ft_itoa(1000
						- (*timeout = 950))))
			exit(EXIT_FAILURE);
	}
	else if (!(p_p_c = ft_itoa(1000
					- (*timeout += 10))))
		exit(EXIT_FAILURE);
	attron(COLOR_PAIR(17));
	draw_line(4, 22, "    ");
	draw_line(4, 22, p_p_c);
	free(p_p_c);
	return (timeout);
}

int			*key_handler(int *timeout, int *ch)
{
	if (*ch == 'e' && *timeout > 0)
		timeout = key_event_e(timeout);
	else if (*ch == 'r' && *timeout > 1)
		timeout = key_event_r(timeout);
	else if (*ch == 'w' && *timeout < 950)
		timeout = key_event_w(timeout);
	else if (*ch == 'q' && *timeout < 950)
		timeout = key_event_q(timeout);
	return (timeout);
}
