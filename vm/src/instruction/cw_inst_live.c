/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_inst_live.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabt <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:06:24 by jabt              #+#    #+#             */
/*   Updated: 2018/10/30 19:15:27 by galemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// ici je dois allez chercher a opcode + 1 4 octets

void    cw_inst_live(t_processus *process)
{
    int             id_champ;
    int             ret;
    unsigned char   *memory;

    if ((ret = get_params(process)) == -1)
    {
        cw_reset_process(process);
        return ;
    }
    memory = arena.memory;
    process->nb_live++;
    id_champ = memory[(process->pc) +1] << 24;
    id_champ += memory[(process->pc + 2)] << 16;
    id_champ += memory[(process->pc + 3)] << 8;
    id_champ += memory[process->pc + 4];
    cw_update_champ_live(id_champ);
    process->pc = (process->pc + ret) & 0xFFF; // c'est ok ca ?
    cw_reset_process(process);
}