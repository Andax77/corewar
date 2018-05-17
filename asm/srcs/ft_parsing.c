/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:37:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/17 20:06:56 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	get_champ_name_comment_other_lines(char **member, int fd)
{
	char	*tmp;

	tmp = NULL;
	while (get_next_line(fd, &tmp) == GNL_SUCCESS)
	{
		if (!strchr(tmp, '"'))
			if (!(*member = ft_str_and_free_join(*member, "\n")))
				exit(EXIT_FAILURE);
		if (!(*member = ft_str_and_free_join(*member, tmp)))
			exit(EXIT_FAILURE);
		if (strchr(tmp, '"'))
		{
			(*member)[ft_strlen(*member) - 1] = '\0';
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

static void	get_champ_name_comment(char *line, char **member, int fd)
{
	int		i;

	i = 0;
	while (*line && *line != '"')
		line++;
	line++;
	while (line[i] && line[i] != '"')
		++i;
	if (!(*member = ft_strndup(line, i)))
		exit(EXIT_FAILURE);
	if (line[i] == '\0')
		get_champ_name_comment_other_lines(member, fd);
//	ft_printf("{magenta}%s\n{eoc}", *member);
}

int			parse_line(char *line, t_champ *champ)
{
	int		is_finished;

	is_finished = 0;
	if (ft_strstr(line, ".name"))
		get_champ_name_comment(line, &champ->name, champ->fd);
	else if (ft_strstr(line, ".comment"))
	{
		get_champ_name_comment(line, &champ->comment, champ->fd);
		++is_finished;
	}
	if (is_finished == 1)
		return (FINISHED);
	return (UNFINISHED);
}
