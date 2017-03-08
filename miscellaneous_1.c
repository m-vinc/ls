/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:48:44 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/08 00:49:39 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_es	init_list(void)
{
	t_es tmp;

	tmp.list = create_element();
	tmp.origin = tmp.list;
	return (tmp);
}

void	w_error(t_stat **s, char *url)
{
	ft_putstr("ft_ls: ");
	perror(url);
	free(s);
}

t_max	zmax(void)
{
	t_max max;

	max.linkmax = 0;
	max.sizemax = 0;
	max.daymax = 0;
	max.majormax = 0;
	max.minormax = 0;
	max.grpmax = 0;
	return (max);
}
