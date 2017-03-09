/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:52:29 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/09 23:48:25 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_element	*get_argtofile(t_arg *hlist, t_flag flag, int *n)
{
	t_es	l;
	t_stat	*s;

	l.list = create_element();
	l.origin = l.list;
	while (hlist->next)
	{
		*n += 1;
		if ((s = malloc(sizeof(t_stat))) == 0 || (lstat(hlist->str, s)) == -1)
		{
			w_perror(hlist->str);
			if (s)
				free(s);
		}
		else if ((S_ISDIR(s->st_mode) && flag.nocontent == 1) ||
				!S_ISDIR(s->st_mode))
			l.list = data_to_element(0, l.list, hlist->str, s);
		else
			free(s);
		hlist = hlist->next;
	}
	return (l.origin);
}

t_element	*get_argtofolder(t_arg *hlist)
{
	t_es	l;
	t_stat	*s;

	l.list = create_element();
	l.origin = l.list;
	while (hlist->next)
	{
		if ((s = malloc(sizeof(t_stat))) == 0 || (lstat(hlist->str, s)) == -1)
		{
			if (s)
				free(s);
		}
		else if (S_ISDIR(s->st_mode))
			l.list = data_to_element(0, l.list, hlist->str, s);
		else
			free(s);
		hlist = hlist->next;
	}
	return (l.origin);
}

t_max		getmajminmax(t_max max, t_element *element)
{
	char	*tmp;
	int		itmp;

	tmp = ft_itoa(major(element->stat->st_rdev));
	itmp = (int)ft_strlen(tmp);
	if (itmp > max.majormax)
		max.majormax = itmp;
	free(tmp);
	tmp = ft_itoa(minor(element->stat->st_rdev));
	itmp = (int)ft_strlen(tmp);
	if (itmp > max.minormax)
		max.minormax = itmp;
	free(tmp);
	return (max);
}

t_max		getgroupmax(t_max max, t_element *element)
{
	int				itmp;
	struct group	*grp;

	grp = getgrgid(element->stat->st_gid);
	itmp = (int)ft_strlen(grp->gr_name);
	if (itmp > max.grpmax)
		max.grpmax = itmp;
	return (max);
}

t_max		getsizemax(t_max max, t_element *element)
{
	char	*tmp;
	int		l;

	tmp = ft_itoa(element->stat->st_size);
	l = ft_strlen(tmp);
	if (l > max.sizemax)
		max.sizemax = l;
	free(tmp);
	return (max);
}
