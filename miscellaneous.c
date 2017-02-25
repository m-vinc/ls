/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:29:21 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/25 17:39:12 by vmorvan          ###   ########.fr       */
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
