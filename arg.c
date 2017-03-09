/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:38:12 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/09 23:56:42 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		argerror(char arg)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(arg);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [-RrltaSfd] [file...]");
	exit(1);
}

t_flag		putflag(t_flag flag, char *arg)
{
	arg++;
	while (*arg)
	{
		if (*arg != 'R' && *arg != 'r' && *arg != 'l' &&
				*arg != 't' && *arg != 'a' && *arg != 'S' && *arg != 'f' &&
				*arg != 'u' && *arg != 'd')
		{
			argerror(*arg);
			exit(1);
		}
		if (*arg == 'R')
			flag.recursive = 1;
		if (*arg == 'r')
			flag.rsort = 1;
		if (*arg == 'l')
			flag.ld = 1;
		if (*arg == 't')
			flag.time = 1;
		if (*arg == 'a')
			flag.all = 1;
		flag = another_flag(*arg, flag);
		arg++;
	}
	return (flag);
}

t_flag		zflag(void)
{
	t_flag flag;

	flag.recursive = 0;
	flag.rsort = 0;
	flag.all = 0;
	flag.ld = 0;
	flag.time = 0;
	flag.size = 0;
	return (flag);
}

t_opt		init_flag(int argc, char **argv)
{
	t_opt	opt;
	int		x;
	uint8_t	endarg;
	t_as	warg;

	opt.flag = zflag();
	warg = init_arglist();
	x = 1;
	endarg = 0;
	while (x < argc)
	{
		if (argv[x][0] == '-' && argv[x][1] != '-' &&
				argv[x][1] != '\0' && endarg == 0)
			opt.flag = putflag(opt.flag, argv[x]);
		else
		{
			warg.list = data_to_arg(argv[x], warg.list);
			endarg = 1;
		}
		x++;
	}
	if (endarg == 0)
		warg.list = data_to_arg(".", warg.list);
	opt.arg = warg.origin;
	return (opt);
}
