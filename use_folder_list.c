/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_folder_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 21:16:28 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/08 05:11:03 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	showfolder_name(t_element *folder)
{
	ft_putstr((folder->path != 0 ? folder->path : folder->name));
	ft_putendl(" :");
}

void	show_flist(int x, t_element *folder, t_opt opt)
{
	int			y;
	t_element	*flist;
	t_element	*dlist;
	t_element	*save;

	save = folder;
	y = element_length(folder);
	while (folder->next)
	{
		if ((y > 1 || x != 0))
			showfolder_name(folder);
		flist = create_list((folder->path != 0 ? folder->path : folder->name),
				opt.flag.all);
		if (flist)
		{
			flist = sort(flist, opt.flag);
			if (opt.flag.recursive == 1)
				dlist = create_dlist(flist);
			y = showfile(flist, opt.flag, 1);
			if (opt.flag.recursive == 1)
				show_flist(y, dlist, opt);
		}
		folder = folder->next;
	}
	wfree_element(save);
}
