#include "ft_ls.h"

void	argerror(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putendl("\nusage: ft_ls [-alrRt]");
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

t_arg	*new_arg()
{
	t_arg *n;
	if ((n = malloc(sizeof(t_arg))) == 0)
		exit(42);
	n->next = 0;
	n->prev = 0;
	n->str = 0;
	return (n);
}
t_arg	*fill_arg(t_arg *actual, char *str, t_arg *next)
{
	if (actual)
	{
		if (str)
			actual->str = ft_strdup(str);
		if (next)
			actual->next = next;
		actual->next->prev = actual;
	}
	else
		fill_arg(new_arg(), str, next);
	return (actual->next);
}
t_element	*new_element()
{
	t_element *n;
	if ((n = malloc(sizeof(t_element))) == 0)
		exit(42);
	n->path = 0;
	n->stat = 0;
	n->prev = 0;
	n->next = 0;
	return (n);
}
t_element	*fill_element(t_element *actual, char *path, t_stat *istat, t_element *next)
{
	if (actual)
	{
		if (path)
			actual->path = ft_strdup(path);
		if (istat)
			actual->stat = istat;
		if (next)
			actual->next = next;
		actual->next->prev = actual;
	}
	else
		fill_element(new_element(), path, istat, next);
	return (actual->next);
}
t_opt	init_opt(int argc, char **argv)
{
	int 	e;
	int 	d;
	t_opt	opt;
	t_arg	*save;

	e = 1;
	d = 0;
	opt.arg = new_arg();
	save = opt.arg;
	while (e < argc)
	{
		if (argv[e][0] == '-' && d == 0)
			if (argv[e][1] == '\0')
				opt.arg = fill_arg(opt.arg, argv[e], new_arg());
			else
				opt.flag = putflag(opt.flag, argv[e]);
		else
		{
			opt.arg = fill_arg(opt.arg, argv[e], new_arg());
			d = 1;
		}
		e++;
	}
	opt.arg = save;
	return (opt);
}
void		free_arg(t_arg *arg)
{
	if (arg->prev)
	{
		if (arg->prev->str)
			free(arg->prev->str);
		free(arg->prev);
		arg->prev = 0;
	}
	
}
void	showfolder(t_element *file, t_opt opt)
{
	while (file->next)
	{
		if (file->path)
			free(file->path);
		file = file->next;
		free(file->prev);
	}
	return ;
}
void	showfirst(t_element *file)
{
	if (S_ISREG(file->stat->st_mode))
		ft_putchar('-');
	if (S_ISDIR(file->stat->st_mode))
		ft_putchar('d');
	if (S_ISCHR(file->stat->st_mode))
		ft_putchar('c');
	if (S_ISBLK(file->stat->st_mode))
		ft_putchar('b');
	if (S_ISFIFO(file->stat->st_mode))
		ft_putchar('p');
	if (S_ISLNK(file->stat->st_mode))
		ft_putchar('l');
	if (S_ISSOCK(file->stat->st_mode))
		ft_putchar('s');
	if (S_ISWHT(file->stat->st_mode))
		ft_putchar('D');
}
void	showright(t_element *file)
{
	ft_putstr( (file->stat->st_mode & S_IRUSR) ? "r" : "-");
	ft_putstr( (file->stat->st_mode & S_IWUSR) ? "w" : "-");
	ft_putstr( (file->stat->st_mode & S_IXUSR) ? "x" : "-");
	ft_putstr( (file->stat->st_mode & S_IRGRP) ? "r" : "-");
	ft_putstr( (file->stat->st_mode & S_IWGRP) ? "w" : "-");
	ft_putstr( (file->stat->st_mode & S_IXGRP) ? "x" : "-");
	ft_putstr( (file->stat->st_mode & S_IROTH) ? "r" : "-");
	ft_putstr( (file->stat->st_mode & S_IWOTH) ? "w" : "-");
	ft_putstr( (file->stat->st_mode & S_IXOTH) ? "x " : "- ");
}
void	showtime(t_element *file)
{
	char 	**time;
	int 	e;
	char 	**s;

	e = 0;
	time = ft_strsplit(ctime(&file->stat->st_ctime), ' ');
	ft_putstr(time[2]);
	ft_putchar(' ');
	ft_putstr(time[1]);
	ft_putchar(' ');
	ft_putstr(time[3]);
	s = time;
	while (time[e] != 0)
	{
		free(time[e]);
		e++;
	}
	free(time[e]);
	free(s);
}
void	showdetail(t_element *file)
{
	struct passwd *pwd;
	struct group *grp;

	grp = getgrgid(file->stat->st_gid);
	pwd = getpwuid(file->stat->st_uid);
	showfirst(file);
	showright(file);
	ft_putnbr(file->stat->st_nlink);
	ft_putchar('\t');
	ft_putstr(pwd->pw_name);
	ft_putchar('\t');
	ft_putstr(grp->gr_name);
	ft_putchar('\t');
	ft_putnbr(file->stat->st_size);
	ft_putchar('\t');
	showtime(file);
	ft_putchar(' ');
	ft_putstr(file->path);
	ft_putchar('\n');
	return ;
}
void	showfile(t_element *file, t_opt opt)
{
	t_element *tmp;

	while (file->next)
	{
		if (opt.flag.ld == 1)
			showdetail(file);
		else
			ft_putendl(file->path);
		if (file->path)
			free(file->path);
		file = file->next;
		free(file->prev);
	}
}

void	process_alist(t_element *file, t_element *folder, t_opt opt)
{
	showfile(file, opt);
	showfolder(folder, opt);
	return ;
}
void		construct_alist(t_opt opt)
{
	t_stat		 s;
	t_element 	*file;
	t_element	*folder;
	t_element	*file_save;
	t_element	*folder_save;

	folder = new_element();
	file = new_element();
	file_save = file;
	folder_save = folder;
	while (opt.arg->next)
	{
		if ((stat(opt.arg->str, &s)) == -1)
			perror("ft_ls");
		else
		{
			if (S_ISDIR(s.st_mode))
				folder = fill_element(folder, opt.arg->str, &s, new_element());
			file = fill_element(file, opt.arg->str, &s, new_element());
		}
		opt.arg = opt.arg->next;
		free_arg(opt.arg);
	}
	process_alist(file_save, folder_save, opt);
}

int main(int argc, char **argv)
{
	t_opt opt;
	t_element *alist;
	opt = init_opt(argc, argv);
	if (opt.arg->str)
		construct_alist(opt);
	else
	{
		opt.arg->str = ft_strdup(".");
		opt.arg->next = new_arg();
		construct_alist(opt);
	}
	while (1);
	exit(0);
}
