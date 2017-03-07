/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:45:48 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/07 22:02:49 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	int			l;
	t_max		max;
	char		*tmp;

	max.linkmax = 0;
	max.sizemax = 0;
	max.daymax = 0;
	l = 0;
	while (element->next)
	{
		tmp = ft_itoa(element->stat->st_nlink);
		if ((int)ft_strlen(tmp) > max.linkmax)
			max.linkmax = ft_strlen(tmp);
		free(tmp);
		if (!S_ISBLK(element->stat->st_mode) &&
				!S_ISCHR(element->stat->st_mode))
		{
			tmp = ft_itoa(element->stat->st_size);
			if ((int)ft_strlen(tmp) > max.sizemax)
				max.sizemax = ft_strlen(tmp);
			free(tmp);
		}
		element = element->next;
	}
	return (max);
}

void	showdetail(t_element *element, t_max max)
{
	char	*f;

	f = ft_strdup("");
	showfirst(element, &f);
	showright(element, &f);
	shownumberinfo(element, &f, max);
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
	int			x;
	t_max		max;

	x = 0;
	save = hflist;
	if (ld == 1 && hflist->name)
	{
		max = init_max(hflist);
		showsize(hflist);
	}
	while (save->next)
	{
		if (ld == 0)
			ft_putendl(save->name);
		else
			showdetail(save, max);
		x++;
		save = save->next;
	}
	wfree_element(hflist);
	return (x);
}
