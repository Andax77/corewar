
#include <corewar.h>

void	cycle(t_cor *cor)
{
	t_champ *ori;
	t_list *champ;
//add stop_vm in 1st while
	champ = cor->champs;
	ori = champ;
	while ((champ = ori))
	{
		while (champ)
		{
			if (((t_champ *)champ->content)->r_cy != -1)
			{
				if (((t_champ *)champ->content)->r_cy == 0)
					exec_op(cor, &champ);
					//He would send a OPcode to exec_op
				(((t_champ *)champ->content)->r_cy)--;
			}
			champ = champ->next;
		}
		(cor->cycle)++;
	}
}

void	exec_op(t_cor *cor, t_champ **champ)
{
	void (**f)(*cor, *champ);

	f[1] = &live;
	f[2] = &ld;
	f[3] = &st;
	f[4] = &add;
	f[5] = &sub;
	f[6] = &f_and;
	f[7] = &f_or;
	f[8] = &f_xor;
	f[9] = &ft_zjmp;
	f[10] = &ldi;
	f[11] = &sti;
	f[12] = &ft_fork;
	f[13] = &lld;
	f[14] = &lldi;
	f[15] = &lfork;
	f[16] = &ft_aff;
}

int		recup_content()
{
	
}

void	ft_aff(t_cor *cor, t_champ  *champ)
{
	int r1;
}
