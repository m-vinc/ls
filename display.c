/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:45:48 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/01 21:04:48 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	showsize(t_element *hfile)
{
	t_element 	*h;
	int 		size;
	char 		*f;
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
void	addtime(char **time, char **f)
{
	int c;

	c = 0;
	*f = ft_strjoinf(*f, time[0]);
	*f = ft_strjoinf(*f, ":");
	*f = ft_strjoinf(*f, time[1]);
	while (time[c] != 0)
	{
		free(time[c]);
		c++;
	}
}

t_max	init_max(t_element *element)
{
	int 		l;
	t_element	*save;
	t_max		max;
	char		*tmp;

	max.linkmax = 0;
	max.sizemax = 0;
	max.daymax = 0;
	save = element;
	l = 0;
	while (save->next)
	{
		tmp = ft_itoa(save->stat->st_nlink);
		if ((int)ft_strlen(tmp) > max.linkmax)
			max.linkmax = ft_strlen(tmp);
		free(tmp);
		tmp = ft_itoa(save->stat->st_size);
		if ((int)ft_strlen(tmp) > max.sizemax)
			max.sizemax = ft_strlen(tmp);
		free(tmp);
		save = save->next;
	}
	return (max);
}

void	showdetail(t_element *element)
{
	char 	*f;

	f = ft_strdup("");
	showfirst(element, &f);
	showright(element, &f);
	shownumberinfo(element, &f);
	showtime(element, &f);
	f = ft_strjoinf(f, " ");
	f = ft_strjoinf(f, element->name);
	if (S_ISLNK(element->stat->st_mode))
		showislink(element, &f);
	f = ft_strjoinf(f, "\n");
	ft_putstr(f);
	free(f);
	return ;
}
void	w_perror(char *str)
{
	ft_putstr("ft_ls: ");
	perror(str);
}
int		showfile(t_element *hflist, uint8_t ld)
{
	t_element	*save;
	int 		x;

	x = 0;
	save = hflist;
	if (ld == 1 && hflist->name)
		showsize(hflist);
	while (save->next)
	{
		if (ld == 0)
			ft_putendl(save->name);
		else
		{
			showdetail(save);
		}
		x++;
		save = save->next;
	}
	wfree_element(hflist);
	return (x);
}
