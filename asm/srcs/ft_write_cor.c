/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 00:43:44 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/21 20:51:04 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	ft_get_instructions_length(t_champ *champ)
{
	t_list		*tmp;
	t_instru	*cur;
	int			ret;

	tmp = champ->instru;
	while (tmp->next != NULL)
		tmp = tmp->next;
	cur = (t_instru *)tmp->content;
	ret = cur->inst_addr + cur->size;
	return (ret);
}

int32_t swap_int32(int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | ((val >> 16) & 0xFFFF);
}
static void	ft_fill_output(t_champ *champ, char *output)
{
	char	*magic;

	magic = ft_malloc(sizeof(COREWAR_EXEC_MAGIC), EXIT_FAILURE);
	*(int *)magic = swap_int32(COREWAR_EXEC_MAGIC);
	ft_memcpy(output, magic, sizeof(COREWAR_EXEC_MAGIC) * 2);
	free(magic);
}

void		ft_write_cor(t_champ *champ, char *name)
{
	char	*output;
	int		length_output;
	int		instructions_length;
	int		s;

	(void)name;
	instructions_length = ft_get_instructions_length(champ);
	ft_printf("{magenta}%d\n{yellow}%d\n{eoc}", instructions_length, sizeof(instructions_length));
	length_output = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 4 + sizeof(instructions_length) + COMMENT_LENGTH + 4 + instructions_length;
	ft_printf("{yellow}%d\n{eoc}", length_output);
	output = ft_malloc(sizeof(char) * (length_output + 1), EXIT_FAILURE);
	ft_bzero(output, length_output + 1);
	ft_fill_output(champ, output);
//	ft_printf("{red}%r{eoc}\n", output, 2215);
	s = open("serge", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	write(s, output, 4);
	free(output);
}
