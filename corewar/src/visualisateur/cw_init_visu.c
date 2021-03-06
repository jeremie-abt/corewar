/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_init_visu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabt <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:17:59 by jabt              #+#    #+#             */
/*   Updated: 2018/11/21 11:02:59 by galemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			cw_set_score_win(void)
{
	g_arena.visu_score = subwin(stdscr, 15, 196,
			WIN_HEIGHT, 1);
	box(g_arena.visu_score, ACS_VLINE, ACS_HLINE);
	mvwprintw(g_arena.visu_score, SC_HEIGHT + 2, SC_FIRST_COL, "cycle : 0");
	mvwprintw(g_arena.visu_score, SC_HEIGHT - 1, SC_SECOND_COL, "LIVE:");
	mvwprintw(g_arena.visu_score, SC_HEIGHT, SC_THIRD_COL, "KEY :");
	mvwprintw(g_arena.visu_score, SC_HEIGHT + 2, SC_THIRD_COL,
			"-play/pause : space");
	mvwprintw(g_arena.visu_score, SC_HEIGHT + 3, SC_THIRD_COL, "-speedup : r");
	mvwprintw(g_arena.visu_score, SC_HEIGHT + 4,
			SC_THIRD_COL, "-slow down : q");
	mvwprintw(g_arena.visu_score, SC_HEIGHT, SC_FOURTH_COL, "Speed :");
	mvwprintw(g_arena.visu_score, SC_HEIGHT + 2, SC_FOURTH_COL, "normal");
	mvwprintw(g_arena.visu_score, SC_HEIGHT_PROC, SC_FOURTH_COL, "Processus :");
	wrefresh(g_arena.visu_score);
}

static void			cw_set_fight_window(void)
{
	int		i;

	i = 1;
	g_arena.visu_fight = subwin(stdscr, WIN_HEIGHT, 196, 0, 1);
	box(g_arena.visu_fight, ACS_VLINE, ACS_HLINE);
	while (i <= 64)
	{
		mvwprintw(g_arena.visu_fight, i, 3, "00 00 00 00 00 00 00 00 00 00 "
			"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
			"00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
			"00 00 00 00 00 00 00 00 00 00 00 00");
		i++;
	}
}

static void			cw_init_color(void)
{
	start_color();
	init_pair(CW_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(CW_PROCESS_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(CW_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(CW_PROCESS_BLUE, COLOR_BLACK, COLOR_BLUE);
	init_pair(CW_RED, COLOR_RED, COLOR_BLACK);
	init_pair(CW_PROCESS_RED, COLOR_BLACK, COLOR_RED);
	init_pair(CW_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(CW_PROCESS_CYAN, COLOR_BLACK, COLOR_CYAN);
}

int					cw_init_visu(void)
{
	int i;

	i = 1;
	initscr();
	curs_set(0);
	noecho();
	timeout(10);
	cw_init_color();
	cw_set_score_win();
	cw_set_fight_window();
	if (!(g_arena.mem_color = malloc(sizeof(g_arena.mem_color) * MEM_SIZE)))
		return (-1);
	ft_bzero(g_arena.mem_color, sizeof(g_arena.mem_color) * MEM_SIZE);
	return (1);
}
