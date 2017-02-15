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
	t_stat stat;

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
char *ft_strjoinf(char *src, char *dest)
{
	char *t;

	t = src;
	src = ft_strjoin(src, dest);
	free(t);
	return (src);
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
int	m_xor(int a, int b)
{
	if (a && b)
		return (1);
	return ((a || b) && !(a && b));
}
void	showfolder(t_element *file, t_opt opt, int c)
{
	t_element 	*tmp;
	int		printfilename;
	
	printfilename = 0;
	if (file->next)
		if (file->next->next)
			printfilename = 1;
	while (file->next)
	{
		if (m_xor(printfilename, c))
		{
			ft_putstr(file->path);
			ft_putendl(" :\n");
		}
		if (file->path)
			free(file->path);
		if (file->stat)
			free(file->stat);
		tmp = file;
		file = file->next;
		if (tmp)
			free(tmp);
	}
	if (file)
		free(file);
	return ;
}
void	showfirst(t_element *file, char **f)
{
	if (S_ISREG(file->stat->st_mode))
		*f = ft_strjoinf(*f, "-");
	if (S_ISDIR(file->stat->st_mode))
		*f = ft_strjoinf(*f, "d");
	if (S_ISCHR(file->stat->st_mode))
		*f = ft_strjoinf(*f, "c");
	if (S_ISBLK(file->stat->st_mode))
		*f = ft_strjoinf(*f, "f");
	if (S_ISFIFO(file->stat->st_mode))
		*f = ft_strjoinf(*f, "p");
	if (S_ISLNK(file->stat->st_mode))
		*f = ft_strjoinf(*f, "l");
	if (S_ISSOCK(file->stat->st_mode))
		*f = ft_strjoinf(*f, "s");
	if (S_ISWHT(file->stat->st_mode))
		*f = ft_strjoinf(*f, "D");
}
void	showright(t_element *file, char **f)
{
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IRUSR) ? "r" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IWUSR) ? "w" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IXUSR) ? "x" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IRGRP) ? "r" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IWGRP) ? "w" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IXGRP) ? "x" : "-");
	*f = ft_strjoinf(*f ,(file->stat->st_mode & S_IROTH) ? "r" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IWOTH) ? "w" : "-");
	*f = ft_strjoinf(*f, (file->stat->st_mode & S_IXOTH) ? "x " : "- ");
}
void	showtime(t_element *file, char **f)
{
	char 	**time;
	int 	e;
	char 	**s;

	e = 0;
	time = ft_strsplit(ctime(&file->stat->st_ctime), ' ');
	*f = ft_strjoinf(*f, time[2]);
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, time[1]);
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, time[3]);
	s = time;
	while (time[e] != 0)
	{
		free(time[e]);
		e++;
	}
	if (time[e])
		free(time[e]);
	if (s)
		free(s);
}
void	shownumberinfo(t_element *file, char **f)
{
	char *tmp;
	struct passwd *pwd;
	struct group *grp;

	grp = getgrgid(file->stat->st_gid);
	pwd = getpwuid(file->stat->st_uid);
	tmp =  ft_itoa(file->stat->st_nlink);
	*f = ft_strjoinf(*f, tmp);
	free(tmp);
	*f = ft_strjoinf(*f, "\t");
	*f = ft_strjoinf(*f, pwd->pw_name);
	*f = ft_strjoinf(*f, "\t");
	*f = ft_strjoinf(*f, grp->gr_name);
	*f = ft_strjoinf(*f, "\t");
	tmp = ft_itoa(file->stat->st_size);
	*f = ft_strjoinf(*f,tmp);
	free(tmp);
	*f = ft_strjoinf(*f, "\t");
}
void	showdetail(t_element *file)
{
	char *f;
	f = strdup("");
	showfirst(file, &f);
	showright(file, &f);
	shownumberinfo(file, &f);
	showtime(file, &f);
	f = ft_strjoinf(f, " ");
	f = ft_strjoinf(f, file->path);
	f = ft_strjoinf(f, "\n");
	ft_putstr(f);
	free(f);
	return ;
}
void	verifyandshow(t_element *file, t_opt opt)
{
		if (opt.flag.all == 1 && file->path[0] == '.')
			if (opt.flag.ld == 1)
				showdetail(file);
			else
				ft_putendl(file->path);
		else if (file->path[0] != '.')
		{
			if (opt.flag.ld == 1)
				showdetail(file);
			else
				ft_putendl(file->path);
		}
}
int	showfile(t_element *file, t_opt opt, uint8_t infolder_flag)
{
	t_element *tmp;
	int c;

	c = 0;
	while (file->path)
	{
		if (!S_ISDIR(file->stat->st_mode))
		{
			verifyandshow(file, opt);
			c++;
		}
		else if (S_ISDIR(file->stat->st_mode) && infolder_flag == 1)
			verifyandshow(file, opt);
		if (file->path)
			free(file->path);
		if (file->stat && !S_ISDIR(file->stat->st_mode))
			free(file->stat);
		tmp = file;
		file = file->next;
		if (tmp)
			free(tmp);
	}
	return (c);
}
void		swap_edata(t_element *un, t_element *deux)
{
	t_stat *save;
	char *tmp;

	save = un->stat;
	un->stat = deux->stat;
	deux->stat = save;
	tmp = un->path;
	un->path = deux->path;
	deux->path = tmp;
}
t_element	*sortlexico(t_element *head)
{
	t_element 	*save;
	uint8_t		swapped;
	char		*s;

	swapped = 1;
	save = head;
	while (swapped)
	{
		swapped = 0;
		while (head->path && head->next->next)
		{
			if (ft_strcmp(head->path, head->next->path) > 0)
			{
				swap_edata(head, head->next);
				head->next->prev = head->prev;
				head->prev = head;
				swapped = 1;
			}
			head = head->next;
		}
		head = save;
	}
	return (save);
}
t_element	*sortrlexico(t_element *head)
{
	t_element 	*save;
	uint8_t		swapped;
	char		*s;

	swapped = 1;
	save = head;
	while (swapped)
	{
		swapped = 0;
		while (head->path && head->next->next)
		{
			if (ft_strcmp(head->path, head->next->path) < 0)
			{
				swap_edata(head, head->next);
				head->next->prev = head->prev;
				head->prev = head;
				swapped = 1;
			}
			head = head->next;
		}
		head = save;
	}
	return (save);
}

t_element	*timesort(t_element *head)
{
	t_element 	*save;
	uint8_t		swapped;

	swapped = 1;
	save = head;
	while (swapped)
	{
		swapped = 0;
		while (head->path && head->next->next)
		{
			if (head->stat->st_ctime < head->next->stat->st_ctime)
			{
				swap_edata(head, head->next);
				head->next->prev = head->prev;
				head->prev = head;
				swapped = 1;
			}
			head = head->next;
		}
		head = save;
	}
	return (save);
}
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- LISAGE DE DOSSIER + REBUILD PATH + CALL + RECURSIVE + TIMESORT == GG*/
void	process_alist(t_element *file, t_element *folder, t_opt opt, uint8_t infolder_flag)
{
	int c;
	
	c = 0;
	file = (opt.flag.rsort == 1 ? sortrlexico(file) : sortlexico(file));
	folder = (opt.flag.rsort == 1 ? sortrlexico(folder) : sortlexico(folder));
	c = showfile((opt.flag.time == 1 ? timesort(file) : file), opt, infolder_flag);
	showfolder((opt.flag.time == 1 ? timesort(folder) : folder), opt, c);
	//showfolder(folder, opt, c);
	return ;
}
/* =-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void		construct_alist(t_opt opt, uint8_t infolder_flag)
{
	t_stat		*s;
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
		if ((s = malloc(sizeof(t_stat))) == 0 || (stat(opt.arg->str, s)) == -1)
			perror("ft_ls");
		else
		{
			if (S_ISDIR(s->st_mode))
				folder = fill_element(folder, opt.arg->str, s, new_element());
			file = fill_element(file, opt.arg->str, s, new_element());
		}
		opt.arg = opt.arg->next;
		free_arg(opt.arg);
	}
	process_alist(file_save, folder_save, opt, infolder_flag);
}

int main(int argc, char **argv)
{
	t_opt opt;
	t_element *alist;
	opt = init_opt(argc, argv);
	if (opt.arg->str)
		construct_alist(opt, 0);
	else
	{
		opt.arg->str = ft_strdup(".");
		opt.arg->next = new_arg();
		construct_alist(opt, 0);
	}
	while (1);
	exit(0);
}
