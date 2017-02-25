/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:45:48 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/25 18:12:52 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	w_perror(char *str)
{
	ft_putstr("ft_ls: ");
	perror(str);
}
void	showfile(t_element *hflist, uint8_t ld)
{
	t_element *save;

	save = hflist;
	while (save->next)
	{
		if (ld == 0)
			ft_putendl(save->name);
		save = save->next;
	}
	wfree_element(hflist);
}
