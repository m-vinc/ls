/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:48:44 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/07 22:06:48 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_es	init_list()
{
	t_es tmp;

	tmp.list = create_element();
	tmp.origin = tmp.list;
	return (tmp);
}

void	w_error(t_stat **s)
{
	perror("ft_ls");
	free(s);
}

