/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_read_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabt <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:39:18 by jabt              #+#    #+#             */
/*   Updated: 2018/11/17 17:53:04 by jabt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "corewar.h"

char				*get_champs_name_by_id(int id)
{
	t_list		*lst_champ;
	t_champion	*champ;

	lst_champ = arena.champion;
	while (lst_champ)
	{
		champ = (t_champion *)lst_champ->content;
		if (champ->id == id)
			return (champ->header.prog_name);
		lst_champ = lst_champ->next;
	}
	return (NULL);
}

int					cw_header_verif_null_byte(unsigned char *buff_file)
{
	buff_file = buff_file + (PROG_NAME_LENGTH + 4);
	if (buff_file[0] || buff_file[1] || buff_file[2] || buff_file[3])
		return (0);
	buff_file = buff_file + (COMMENT_LENGTH + 8);
	if (buff_file[0] || buff_file[1] || buff_file[2] || buff_file[3])
		return (0);
	return (42);
}

/*
** 		for understanding max_len_file :
** 		https://42born2code.slack.com/messages/GCTSC1V39/convo
**		/C3QG85SG6-1536486698.000100/
*/

int					cw_read_champion(char *champ_name, int id)
{
	int				fd;
	int				max_len_file;
	unsigned char	*buffer;
	size_t			ret;

	if (arena.nb_champ >= MAX_PLAYERS)
	{
		printf("Corewar : too much champion\n");
		return (-1);
	}
	arena.nb_champ++;
	max_len_file = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE;
	if (!(buffer = ft_memalloc(max_len_file)))
		return (-1);
	if ((fd = open(champ_name, O_RDONLY)) == -1 ||
			(ret = read(fd, buffer, max_len_file)) == -1)
	{
		perror("corewar ");
		free(buffer);
		return (-1);
	}
	if (cw_add_new_champ(buffer, ret, champ_name, id) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	close(fd);
	return (1);
}
