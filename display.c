/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:45:48 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/26 17:11:25 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	while (save->next)
	{
		if (ld == 0)
			ft_putendl(save->name);
		x++;
		save = save->next;
	}
	wfree_element(hflist);
	return (x);
}
