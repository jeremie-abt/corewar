/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_inst_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabt <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:14:06 by jabt              #+#    #+#             */
/*   Updated: 2018/11/07 18:11:07 by galemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    cw_inst_fork(t_processus *process)
{
	unsigned int	param;
	unsigned int	pc;
	t_processus		*new_processus;

	param = cw_calculate_value_on_ram(process->pc + 1, 2);
	pc = apply_IDX_MOD(process->pc, MEM_MASK(process->pc + param));

	new_processus = malloc(sizeof(t_processus));
	memcpy(new_processus, process, sizeof(t_processus));
	new_processus->pc = pc;
	ft_lstappend(&arena.process, ft_lstnew(new_processus, sizeof(t_processus)));
	free(new_processus);
	process->pc = MEM_MASK(process->pc + 3);
}
