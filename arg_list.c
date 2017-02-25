/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:34:59 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/25 17:00:25 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_arg	*create_arg()
{
	t_arg	*new;
	if ((new = malloc(sizeof(t_arg))) == 0)
	{
		perror("ft_ls");
		exit(42);
	}
	new->str = 0;
	new->next = 0;
	return (new);
}

t_arg	*data_to_arg(char *str, t_arg *obj)
{
	obj->str = ft_strdup(str);
	obj->next = create_arg();
	return (obj->next);
}
void	wfree_arg(t_arg *harg)
{
	t_arg *tmp;

	while (harg)
	{
		if (harg->str)
			free(harg->str);
		tmp = harg;
		harg = harg->next;
		free(tmp);
	}
}
