/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:29:31 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/16 16:15:04 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		ft_parse_status(t_champ *champ, int status)
{
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

int		ft_name_comment_other_lines_next(char **member, char *tmp)
{
	int		i;
	int		index;
	int		count;

	i = -1;
	count = 0;
	index = 0;
	while ((*member)[++i])
		if ((*member)[i] == '"')
		{
			index = i;
			++count;
		}
	if (count != 1 && ft_fruit(1, &tmp))
		return (ERROR);
	i = index;
	while ((*member)[++i])
		if ((*member)[i] == COMMENT_CHAR)
			break ;
		else if ((*member)[i] != ' ' && (*member)[i] != '\t'
				&& ft_fruit(1, &tmp))
			return (ERROR);
	(*member)[index] = '\0';
	free(tmp);
	return (SUCCESS);
}

int		ft_verif_format_name(char *str)
{
	int		i;

	i = -1;
	while (str[++i] == ' ' || str[i] == '\t')
		;
	if (ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
		return (ERROR);
	i += ft_strlen(NAME_CMD_STRING);
	while (str[++i] && str[i] != '"')
		if (str[i] != ' ' && str[i] != '\t')
			return (ERROR);
	return (SUCCESS);
}

int		ft_verif_format_comment(char *str)
{
	int		i;

	i = -1;
	while (str[++i] == ' ' || str[i] == '\t')
		;
	if (ft_strncmp(str + i, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)) != 0)
		return (ERROR);
	i += ft_strlen(COMMENT_CMD_STRING);
	while (str[++i] && str[i] != '"')
		if (str[i] != ' ' && str[i] != '\t')
			return (ERROR);
	return (SUCCESS);
}

int		ft_verif_register(t_champ *champ)
{
	t_list		*tmp;
	t_instru	*cur;
	int			i;

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		if (cur->params)
		{
			i = -1;
			while (cur->params[++i])
				if (cur->params[i][0] == 'r')
				{
					if (!ft_strisdigit(cur->params[i] + 1))
						return (ft_error(champ, "error: wrong reg number"));
					else if (ft_atoi(cur->params[i] + 1) <= 0
							|| ft_atoi(cur->params[i] + 1) > REG_NUMBER)
						return (ft_error(champ,
									"error: reg num is too low or too high"));
				}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
