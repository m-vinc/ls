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
	n->path = 0;
	return (n);
}
t_arg	*fill_arg(t_arg *actual, char *str, char *path, t_arg *next)
{
	if (actual)
	{
		if (str)
			actual->str = ft_strdup(str);
		if (path != 0)
			actual->path = path;
		if (next)
			actual->next = next;
		actual->next->prev = actual;
	}
	else
		fill_arg(new_arg(), str, path, next);
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
	n->realpath = 0;
	return (n);
}
t_element	*fill_element(t_element *actual, char *path, char *basepath, t_stat *istat, t_element *next)
{
	t_stat stat;

	if (actual)
	{
		if (path)
			actual->path = ft_strdup(path);
		if (istat)
			actual->stat = istat;
		if (basepath)
			actual->realpath = basepath;
		if (next)
			actual->next = next;
		actual->next->prev = actual;
	}
	else
		fill_element(new_element(), path, basepath, istat, next);
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
t_flag	init_flag()
{
	t_flag flag;

	flag.recursive = 0;
	flag.ld = 0;
	flag.time = 0;
	flag.rsort = 0;
	flag.all = 0;
	return (flag);
}
t_opt	init_opt(t_opt opt,int argc, char **argv)
{
	int 	e;
	int 	d;
	t_arg	*save;

	e = 1;
	d = 0;
	opt.arg = new_arg();
	opt.flag = init_flag();
	save = opt.arg;
	while (e < argc)
	{
		if (argv[e][0] == '-' && d == 0)
			if (argv[e][1] == '\0')
				opt.arg = fill_arg(opt.arg, argv[e], 0, new_arg());
			else
				opt.flag = putflag(opt.flag, argv[e]);
		else
		{
			opt.arg = fill_arg(opt.arg, argv[e], 0, new_arg());
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
void	m_xor(int a, int b, char *filename)
{
	if (a && b)
	{
		ft_putchar('\n');
		ft_putstr(filename);
		ft_putendl(" :\n");
		return ;
	}
	if ((a || b) && !(a && b))
	{
		ft_putchar('\n');
		ft_putstr(filename);
		ft_putendl(" :\n");
		return ;
	}
}
char 	*build_path(char *base, char *file)
{
	char 	*p;
	char 	*tmp;

	p = 0;
	p = (base[ft_strlen(base) - 1] != '/' ? ft_strjoin(base, "/") : p);
	tmp = p;
	if (p != 0)
		p = ft_strjoinf(p, file);
	else
		p = ft_strjoin(base, file);
	return (p);
}
t_arg	*read_file(t_opt opt, t_element *file)
{
	t_dirent	*info;
	t_stat		*s;
	t_arg		*f;
	t_arg		*save;
	DIR		*sf;
	
	sf = 0;
	f = new_arg();
	save = f;
	if ((sf = opendir(file->realpath)) == 0)
		perror("ft_lsx");
	else
	{
		while ((info = readdir(sf)))
		{
			f = fill_arg(f, info->d_name, build_path(file->realpath, info->d_name), new_arg());
		}
		(void)closedir(sf);
	}
	return (save);	
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
		m_xor(printfilename, c, file->realpath);
		if ((opt.arg = read_file(opt, file)) && opt.flag.recursive == 1)
			construct_alist(opt, 1, 1);
		else
			construct_alist(opt, 1, 0);
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
		*f = ft_strjoinf(*f, "b");
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
void	addtime(char **time, char **f)
{
	int c;

	c = 0;
	*f = ft_strjoinf(*f, time[0]);
	*f = ft_strjoinf(*f, ":");
	*f = ft_strjoinf(*f, time[1]);
	free(time[1]);
	free(time[0]);
	free(time[3]);
}
void	showtime(t_element *file, char **f)
{
	char 	**time;
	int 	e;
	char 	**s;
	char 	**hour;

	e = 0;
	time = ft_strsplit(ctime(&file->stat->st_ctime), ' ');
	*f = ft_strjoinf(*f, time[2]);
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, time[1]);
	*f = ft_strjoinf(*f, " ");
	hour = ft_strsplit(time[3], ':');
	addtime(hour, f);
	free(hour);
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
char	*get_majorminor(t_element *file)
{
	char *p;
	char *tmp;

	p = ft_strdup("");
	tmp = ft_itoa(major(file->stat->st_rdev));
	p = ft_strjoinf(p, tmp);
	free(tmp);
	p = ft_strjoinf(p, ", ");
	tmp = ft_itoa(minor(file->stat->st_rdev));
	p = ft_strjoinf(p, tmp);
	free(tmp);
	return (p);
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
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, grp->gr_name);
	*f = ft_strjoinf(*f, "\t");
	tmp = (S_ISCHR(file->stat->st_mode) || S_ISBLK(file->stat->st_mode) ? get_majorminor(file) : ft_itoa(file->stat->st_size));
	*f = ft_strjoinf(*f,tmp);
	free(tmp);
	*f = ft_strjoinf(*f, "\t");
}
void	showislink(t_element *file, uint8_t iff, char **f)
{
	char 	*rl;
	int 	nc;

	if ((rl = malloc(sizeof(char) * file->stat->st_size + 1)) == 0)
		perror("ft_lsq");
	else
	{
		if ((nc = readlink((iff == 1 ? file->realpath : file->path), rl, file->stat->st_size + 1)) == -1)
			perror("ft_lse");
		else
			rl[file->stat->st_size] = '\0';
		*f = ft_strjoinf(*f, " ");
		*f = ft_strjoinf(*f, "-> ");
		*f = ft_strjoinf(*f, rl);
	}
}
void	showdetail(t_element *file, uint8_t iff)
{
	char 		*f;
	unsigned int	nc;

	f = ft_strdup("");
	showfirst(file, &f);
	showright(file, &f);
	shownumberinfo(file, &f);
	showtime(file, &f);
	f = ft_strjoinf(f, " ");
	f = ft_strjoinf(f, file->path);
	if (S_ISLNK(file->stat->st_mode))
		showislink(file, iff, &f);
	f = ft_strjoinf(f, "\n");
	ft_putstr(f);
	free(f);
	return ;
}
void	verifyandshow(t_element *file, t_opt opt, uint8_t iff)
{
		if (opt.flag.all == 1 && file->path[0] == '.')
			if (opt.flag.ld == 1)
				showdetail(file, iff);
			else
				ft_putendl(file->path);
		else if (file->path[0] != '.')
		{
			if (opt.flag.ld == 1)
				showdetail(file, iff);
			else
				ft_putendl(file->path);
		}
}

void	showsize(t_element *hfile, t_opt opt)
{
	t_element 	*h;
	int 		size;
	char 		*f;
	char		*save;

	f = ft_strdup("");
	size = 0;
	h = hfile;
	while (hfile->next)
	{
		if ((hfile->path[0] == '.' && opt.flag.all == 1) || hfile->path[0] != '.')
			size += hfile->stat->st_blocks;
		hfile = hfile->next;
	}
	f = ft_strjoinf(f, "total ");
	save = ft_itoa(size);
	f = ft_strjoinf(f, save);
	free(save);
	f = ft_strjoinf(f, "\n");
	ft_putstr(f);
	free(f);
	hfile = h;
}
int	showfile(t_element *file, t_opt opt, uint8_t infolder_flag)
{
	t_element *tmp;
	int c;

	c = 0;
	if (opt.flag.ld == 1 && infolder_flag == 1 && file->stat)
		showsize(file, opt);
	while (file->path)
	{
		if (!S_ISDIR(file->stat->st_mode))
		{
			verifyandshow(file, opt, infolder_flag);
			c++;
		}
		else if (S_ISDIR(file->stat->st_mode) && infolder_flag == 1)
			verifyandshow(file, opt, infolder_flag);
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
	tmp = 0;
	if (un->realpath && deux->realpath)
	{
		tmp = un->realpath;
		un->realpath = deux->realpath;
		deux->realpath = tmp;
	}
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
	t_element 	*end;
	char 		*s;
	save = head;
	while (head->next)
		head = head->next;
	end = head;
	head = save;
	ft_putchar('x');
	while(end->prev)
	{
		if (end->path)
		{
			swap_edata(head, end);
			head = head->next;
		}
		end = end->prev;
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
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- TIMESORT + LEAKS + PADDING == GG*/
void	process_alist(t_element *file, t_element *folder, t_opt opt, uint8_t infolder_flag)
{
	int c;
	
	c = 0;
	c = showfile(sortlexico(file), opt, infolder_flag); // condition -a -l -t -l
	showfolder(sortlexico(folder), opt, c);
	//showfolder(folder, opt, c);
	return ;
}
/* =-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void		recurseofnot(t_element *file, t_element *folder, uint8_t infolder_flag, uint8_t r, t_opt opt)
{
	int c;

	if (r == 1)
	{
		process_alist(file, folder, opt, infolder_flag);
	}
	else
	{
		c = showfile(sortlexico(file), opt, infolder_flag);//condition pour -a -l -r -t
	}
}
t_element	*antiloop(t_element *actual, t_opt opt, t_stat *s, uint8_t r, uint8_t iff)
{
	if (r == 1 && iff == 1)
	{
		if (ft_strcmp(opt.arg->str, ".") != 0 && ft_strcmp(opt.arg->str, "..") != 0)
		{
			if (opt.arg->str[0] == '.')
			{
				if (opt.flag.all == 1)
					actual = fill_element(actual, opt.arg->str, opt.arg->path, s, new_element());
			}
			else
				actual = fill_element(actual, opt.arg->str, opt.arg->path, s, new_element());
		}
	}
	else
		actual = fill_element(actual, opt.arg->str, opt.arg->path, s, new_element());
	return (actual);
}
void		construct_alist(t_opt opt, uint8_t infolder_flag, uint8_t r)
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
		if ((s = malloc(sizeof(t_stat))) == 0 || (lstat((infolder_flag == 1 ? opt.arg->path : opt.arg->str), s)) == -1)
			perror("ft_ls");
		else
		{
			if (S_ISDIR(s->st_mode) && (opt.arg->path = ft_strjoin((infolder_flag == 1 ? opt.arg->path : opt.arg->str), "/")))
				folder = antiloop(folder, opt, s, r, infolder_flag);
			file = fill_element(file, opt.arg->str, opt.arg->path, s, new_element());
		}
		opt.arg = opt.arg->next;
		free_arg(opt.arg);
	}
	recurseofnot(file_save, folder_save, infolder_flag, r, opt);	
}

int main(int argc, char **argv)
{
	t_opt opt;
	t_element *alist;
	opt = init_opt(opt, argc, argv);
	if (opt.arg->str)
		construct_alist(opt, 0, 1);
	else
	{
		opt.arg->str = ft_strdup(".");
		opt.arg->next = new_arg();
		construct_alist(opt, 0, 1);
	}
	exit(0);
}
