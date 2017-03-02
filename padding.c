/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:52:38 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/02 18:39:44 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	padding(char *data, char **str, int max)
{
	int		l;
	int		c;

	l = ft_strlen(data);
	c = max - l;
	if (l > max)
		return ;
	while (c--)
	{
		ft_putnbr(c);
		*str = ft_strjoinf(*str, " ");
	}
}
