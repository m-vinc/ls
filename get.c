/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:52:29 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/26 17:38:56 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


t_element	*get_argtofile(t_arg *hlist)
{
	t_es	l;
	t_stat	*s;

	l.list = create_element();
	l.origin = l.list;
	while (hlist->next)
	{
		if ((s = malloc(sizeof(t_stat))) == 0 || (lstat(hlist->str, s)) == -1)
		{
			w_perror(hlist->str);
			if (s)
				free(s);
		}
		else if (!S_ISDIR(s->st_mode))
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
	t_stat 	*s;

	l.list = create_element();
	l.origin = l.list;
	while (hlist->next)
	{
		if ((s = malloc(sizeof(t_stat))) == 0 || (lstat(hlist->str, s)) == -1)
		{
			w_perror(hlist->str);
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

