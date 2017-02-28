/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:14:09 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/28 11:06:26 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_opt 		opt;
	int 		x;
	t_element	*folder;

	x = 0;
	opt = init_flag(argc, argv);
	x = showfile(sort(get_argtofile(opt.arg), opt.flag), opt.flag.ld);
	folder = sort(get_argtofolder(opt.arg), opt.flag);
	show_flist(x, folder, opt);
	wfree_arg(opt.arg);
	exit(0);
}
