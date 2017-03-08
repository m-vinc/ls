/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 04:32:48 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/08 05:22:52 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_element	*sorttime(t_element *hlist)
{
	t_element	*save;
	uint8_t		swapped;

	swapped = 1;
	save = hlist;
	while (swapped)
	{
		swapped = 0;
		while (hlist->name && hlist->next->next)
		{
			if (hlist->stat->st_ctime < hlist->next->stat->st_ctime)
			{
				swap_edata(hlist, hlist->next);
				swapped = 1;
			}
			hlist = hlist->next;
		}
		hlist = save;
	}
	return (save);
}

t_element	*sorttime_u(t_element *hlist)
{
	t_element	*save;
	uint8_t		swapped;

	swapped = 1;
	save = hlist;
	while (swapped)
	{
		swapped = 0;
		while (hlist->name && hlist->next->next)
		{
			if (hlist->stat->st_atime > hlist->next->stat->st_atime)
			{
				swap_edata(hlist, hlist->next);
				swapped = 1;
			}
			hlist = hlist->next;
		}
		hlist = save;
	}
	return (save);
}
