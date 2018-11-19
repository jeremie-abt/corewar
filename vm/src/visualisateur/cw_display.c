/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabt <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:07:03 by jabt              #+#    #+#             */
/*   Updated: 2018/11/19 13:28:26 by jabt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_champ_color(t_champion *champ)
{
	static int		color;

	color++;
	if (color == 1)
	{
		champ->color = CW_GREEN;
		return (CW_GREEN);
	}
	else if (color == 2)
	{
		champ->color = CW_BLUE;
		return (CW_BLUE);
	}
	else if (color == 3)
	{
		champ->color = CW_RED;
		return (CW_RED);
	}
	else
	{
		champ->color = CW_CYAN;
		return (CW_CYAN);
	}
}

void			cw_display_champ_on_ram(t_champion *champ, t_processus *process)
{
	int				i;
	unsigned int	pc;
	int				color_pair;

	color_pair = cw_champ_color(champ);
	pc = process->pc;
	i = 0;
	wattron(arena.visu_fight, COLOR_PAIR(color_pair));
	wattron(arena.visu_fight, WA_STANDOUT);
	mvwprintw(arena.visu_fight, (pc / 64) + 1, ((pc % 64) * 3) + 3,
			"%.2X", arena.memory[pc]);
	wattroff(arena.visu_fight, WA_STANDOUT);
	ft_memset(&arena.mem_color[pc], color_pair, champ->header.prog_size);
	i++;
	pc++;
	while (i < champ->header.prog_size)
	{
		mvwprintw(arena.visu_fight, (pc / 64) + 1, ((pc % 64) * 3) + 3,
				"%.2X ", arena.memory[pc]);
		pc++;
		i++;
	}
	wattroff(arena.visu_fight, COLOR_PAIR(color_pair));
}

void			cw_visu_incr_process(t_processus *process, int next_pc)
{
	int		cur_pc;

	cur_pc = process->pc;
	wattron(arena.visu_fight, COLOR_PAIR(arena.mem_color[cur_pc]));
	mvwprintw(arena.visu_fight, (cur_pc / 64) + 1, ((cur_pc % 64) * 3) + 3,
			"%.2X", arena.memory[cur_pc]);
	wattroff(arena.visu_fight, COLOR_PAIR(arena.mem_color[cur_pc]));
	wattron(arena.visu_fight, COLOR_PAIR(arena.mem_color[next_pc]));
	wattron(arena.visu_fight, WA_STANDOUT);
	mvwprintw(arena.visu_fight, (next_pc / 64) + 1, ((next_pc % 64) * 3) + 3,
			"%.2X", arena.memory[next_pc]);
	wattroff(arena.visu_fight, WA_STANDOUT);
	wattroff(arena.visu_fight, COLOR_PAIR(arena.mem_color[next_pc]));
}

void			cw_print_winner_visu(void)
{
	t_list		*lst_champ;
	t_champion	*champ;
	int			i;

	i = 0;
	lst_champ = arena.champion;
	while (lst_champ)
	{
		i++;
		champ = (t_champion *)lst_champ->content;
		if (champ->id == arena.id_last_player_alive)
		{
			wattron(arena.visu_score, COLOR_PAIR(champ->color));
			mvwprintw(arena.visu_score, SC_HEIGHT + 1, SC_FIRST_COL + 25,
					"Thewinner is %s!\n",
					get_champs_name_by_id(arena.id_last_player_alive));
			wattroff(arena.visu_score, COLOR_PAIR(champ->color));
			wrefresh(arena.visu_score);
			return ;
		}
		lst_champ = lst_champ->next;
	}
}
