/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:14:16 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/07 21:17:17 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	showsize(t_element *hfile)
{
	t_element	*h;
	int			size;
	char		*f;
	char		*save;

	f = ft_strdup("");
	size = 0;
	h = hfile;
	while (hfile->next)
	{
		size += hfile->stat->st_blocks;
		hfile = hfile->next;
	}
	f = ft_strjoinf(f, "total ");
	save = ft_itoa(size);
	f = ft_strjoinf(f, save);
	free(save);
	f = ft_strjoinf(f, "\n");
	ft_putstr(f);
	free(f);
	hfile = h;
}
