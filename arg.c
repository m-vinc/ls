/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:38:12 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/10 01:36:42 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		argerror(char arg)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: ft_ls [-RrltauSfd] [file...]", 2);
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

t_arg		*addtolist(t_arg *list, char *arg, uint8_t *ea, int *n)
{
	if (*ea == 0 && arg[0] == '-' && arg[1] == '-' && arg[2] == '\0')
		*ea = 1;
	else
	{
		list = data_to_arg(arg, list);
		*ea = 1;
		*n = *n + 1;
	}
	return (list);
}

t_opt		init_flag(int argc, char **argv)
{
	t_opt	opt;
	int		x;
	uint8_t	endarg;
	t_as	warg;
	int		n;

	opt.flag = zflag();
	warg = init_arglist();
	x = 1;
	n = 0;
	endarg = 0;
	while (x < argc)
	{
		if (argv[x][0] == '-' && argv[x][1] != '-' &&
				argv[x][1] != '\0' && endarg == 0)
			opt.flag = putflag(opt.flag, argv[x]);
		else
			warg.list = addtolist(warg.list, argv[x], &endarg, &n);
		x++;
	}
	if (n == 0)
		warg.list = data_to_arg(".", warg.list);
	opt.arg = warg.origin;
	return (opt);
}
