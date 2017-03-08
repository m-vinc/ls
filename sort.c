/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 17:28:15 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/08 04:43:21 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		swap_edata(t_element *un, t_element *deux)
{
	t_stat	*save;
	char	*tmp;

	save = un->stat;
	un->stat = deux->stat;
	deux->stat = save;
	tmp = un->name;
	un->name = deux->name;
	deux->name = tmp;
	tmp = 0;
	if (un->path && deux->path)
	{
		tmp = un->path;
		un->path = deux->path;
		deux->path = tmp;
	}
}

t_element	*sortlexico(t_element *hlist)
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
			if (ft_strcmp(hlist->name, hlist->next->name) > 0)
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

t_element	*sortreverse(t_element *hlist)
{
	t_element	*save;
	int			l;
	int			c;
	int			e;

	e = 0;
	c = 0;
	l = element_length(hlist);
	save = hlist;
	while (c < l)
	{
		while (hlist->name && hlist->next && e < (l - c) - 1)
		{
			if (hlist->next->next)
				swap_edata(hlist, hlist->next);
			hlist = hlist->next;
			e++;
		}
		e = 0;
		hlist = save;
		c++;
	}
	return (save);
}

t_element	*sortsize(t_element *hlist)
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
			if (hlist->stat->st_size < hlist->next->stat->st_size)
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

t_element	*sort(t_element *hlist, t_flag flag)
{
	if (flag.nosort != 1)
		hlist = sortlexico(hlist);
	if (flag.time == 1)
	{
		if (flag.accesstime == 1)
			hlist = sorttime_u(hlist);
		else
			hlist = sorttime(hlist);
	}
	if (flag.size == 1)
		hlist = sortsize(hlist);
	if (flag.rsort == 1)
		hlist = sortreverse(hlist);
	return (hlist);
}
