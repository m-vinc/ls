/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:14:09 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/25 18:14:09 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_opt opt;
	t_arg *s;

	opt = init_flag(argc, argv);
	showfile(get_argtofile(opt.arg), opt.flag.ld);
	wfree_arg(opt.arg);
	exit(0);
}
