/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:52:38 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/08 01:30:13 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	padding_grp(char *gr_name, t_max max, char **str)
{
	int		l;
	int		space;

	*str = ft_strjoinf(*str, "  ");
	l = (int)ft_strlen(gr_name);
	space = max.grpmax - l;
	while (space--)
		*str = ft_strjoinf(*str, " ");
}

void	padding_mm(t_element *element, t_max max, char **str)
{
	char	*tmp;
	int		l;
	int		space;

	tmp = ft_itoa(major(element->stat->st_rdev));
	l = (int)ft_strlen(tmp);
	space = max.majormax - l;
	while (space--)
		*str = ft_strjoinf(*str, " ");
	*str = ft_strjoinf(*str, tmp);
	*str = ft_strjoinf(*str, ", ");
	free(tmp);
	tmp = ft_itoa(minor(element->stat->st_rdev));
	l = (int)ft_strlen(tmp);
	space = max.minormax - l;
	while (space--)
		*str = ft_strjoin(*str, " ");
	*str = ft_strjoin(*str, tmp);
	free(tmp);
}

void	padding(char *data, char **str, t_max max, t_element *element, uint8_t mode)
{
	int		l;
	int		c;
	
	if (data == 0)
		padding_mm(element, max, str);
	else
	{
		l = ft_strlen(data);
		c = (mode == 0 ? max.linkmax : max.sizemax) - l;
		if (l == max.sizemax)
			return ;
		if (l > max.sizemax)
			return ;
		while (c > 0)
		{
			*str = ft_strjoinf(*str, " ");
			c--;
		}
	}
}
