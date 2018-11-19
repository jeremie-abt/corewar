/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:29:41 by femaury           #+#    #+#             */
/*   Updated: 2018/06/14 15:56:02 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisdigit(const char *s)
{
	if (*s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	return (*s ? 0 : 1);
}
