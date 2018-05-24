/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:37:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/24 23:22:08 by pmilan           ###   ########.fr       */
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

static int	get_champ_name_comment(char *line, char **member, int fd)
{
	int		i;

	i = 0;
	while (*line && *line != '"')
		line++;
	if (*line == '\0')
		return (ERROR);
	line++;
	while (line[i] && line[i] != '"')
		++i;
	if (!(*member = ft_strndup(line, i)))
		exit(EXIT_FAILURE);
	if (line[i] == '\0')
		get_champ_name_comment_other_lines(member, fd);
	return (SUCCESS);
}

int			parse_line(char *line, t_champ *champ)
{
	int		status;

	status = SUCCESS;
	if (line[0] == COMMENT_CHAR)
		return (UNFINISHED);
	if (ft_strstr(line, ".name"))
		status = get_champ_name_comment(line, &champ->name, champ->fd);
	else if (ft_strstr(line, ".comment"))
		status = get_champ_name_comment(line, &champ->comment, champ->fd);
	if (status == ERROR)
		return (ft_error(champ, "error: name or comment is badly formatted"));
	if (champ->name && ft_strlen(champ->name) > PROG_NAME_LENGTH)
		return (ft_error(champ, "error: program name is too long"));
	if (champ->comment && ft_strlen(champ->comment) > COMMENT_LENGTH)
		return (ft_error(champ, "error: program comment is too long"));
	if (champ->name != NULL && champ->comment != NULL)
		return (FINISHED);
	return (UNFINISHED);
}
