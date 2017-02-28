#include "ft_ls.h"

void	argerror(char arg)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(arg);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [-Rrlta] [file...]");
	exit(0);
}
t_flag	putflag(t_flag flag, char *arg)
{
	arg++;
	while (*arg)
	{
		if (*arg != 'R' && *arg != 'r' && *arg != 'l' && *arg != 't' && *arg != 'a')
		{
			argerror(*arg);
			exit(0);
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
		arg++;
	}
	return (flag);
}

t_flag zflag()
{
	t_flag flag;

	flag.recursive = 0;
	flag.rsort = 0;
	flag.all = 0;
	flag.ld = 0;
	flag.time = 0;
	return (flag);
}

t_opt	init_flag(int argc, char **argv)
{
	t_opt	opt;
	int 	x;
	uint8_t	endarg;
	t_as	warg;

	opt.flag = zflag();
	warg.list = create_arg();
	warg.origin = warg.list;
	x = 1;
	endarg = 0;
	while (x < argc)
	{
		if (argv[x][0] == '-' && endarg == 0)
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
