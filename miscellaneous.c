/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:29:21 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/26 21:12:33 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			element_length(t_element *hlist)
{
	int 		x;
	t_element 	*save;

	x = 0;
	save = hlist;
	while (save->next)
	{
		x++;
		save = save->next;
	}
	return (x);
}
int			arg_length(t_arg *hlist)
{
	int			x;
	t_arg		*save;

	save = hlist;
	x = 0;
	while (save->next)
	{
		x++;
		save = save->next;
	}
	return (x);
}
char *ft_strjoinf(char *src, char *dest)
{
	char *t;

	t = src;
	src = ft_strjoin(src, dest);
	if (t)
		free(t);
	return (src);
}
char	*build_path(char *base, char *name)
{
	char *tmp;
	char *final;

	tmp = ft_strjoin(base, "/");
	final = ft_strjoin(tmp, name);
	free(tmp);
	return (final);
}