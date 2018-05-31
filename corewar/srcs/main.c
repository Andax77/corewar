/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/31 17:24:58 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void		del_champ(void *content, size_t content_size)
{
	(void)content_size;
	free(((t_champ*)content)->name);
	free(((t_champ*)content)->comment);
	free(((t_champ*)content)->prog);
	free(((t_champ*)content)->splited_prog);
	ft_lstdel(&((t_champ*)content)->instru, del);
	free(content);
}

static void	free_cor(t_cor *cor)
{
	free(cor->opt);
	ft_lstdel(&(cor->champs), del_champ);
	free(cor->map);
	free(cor);
}

int			main(int argc, char **argv)
{
	t_opt	*opt;
	t_cor	*cor;

	opt = ft_malloc(sizeof(t_opt), EXIT_FAILURE);
	cor = ft_malloc(sizeof(t_cor), EXIT_FAILURE);
	if (argc == 1)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	else if (parse_opt(argv, opt, cor) == ERROR)
	{
		print_usage();
		free_cor(cor);
		exit(EXIT_FAILURE);
	}
	else if (init(argv, cor) == ERROR)
	{
		free_cor(cor);
		exit(EXIT_FAILURE);
	}
	free_cor(cor);
	exit(EXIT_SUCCESS);
}
