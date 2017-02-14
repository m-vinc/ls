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

t_arg	*new_arg(char *str, t_arg *actual)
{
	t_arg *n;

	if ((n = malloc(sizeof(t_arg))) == 0)
		exit(0);
	n->str = ft_strdup(str);
	n->prev = 0;
	n->next = 0;
	if (actual)
	{
		actual->next = n;
		actual->next->prev = actual;
		actual = actual->next;
	}
	else
		actual = n;
	return (actual);
}
/*
t_element	*new_element(char *str, t_stat *sinfo)
{
	t_element *n;

	if ((n = malloc(sizeof(t_element))) == 0)
		exit(42);
	if (str)
		n->path = ft_strdup(str);
	n->prev = 0;
	n->next = 0;
	if (sinfo)
		n->stat = sinfo;
	return (n);
}
*/
t_element	*new_element(char *str, t_element *actual, t_stat *sinfo)
{
	t_element *n;

	if ((n = malloc(sizeof(t_element))) == 0)
		exit(0);
	n->path = ft_strdup(str);
	n->prev = 0;
	n->next = 0;
	n->stat = sinfo;
	if (actual)
	{
		actual->next = n;
		actual->next->prev = actual;
		actual = actual->next;
	}
	else
		actual = n;
	return (actual);
}
t_dir	*new_dir(t_element *folder, t_dir *actual)
{
	t_dir *n;

	if ((n = malloc(sizeof(t_dir))) == 0)
		exit(0);
	n->dir = folder;
	n->prev = 0;
	n->next = 0;
	if (actual)
	{
		actual->next = n;
		actual->next->prev = actual;
		actual = actual->next;
	}
	else
		actual = n;
	return (actual);
}

t_opt	init_opt(int argc, char **argv)
{
	int 	e;
	int 	d;
	t_opt	opt;

	e = 1;
	d = 0;
	while (e < argc)
	{
		if (argv[e][0] == '-' && d == 0)
		{
			if (argv[e][1] == '\0')
			{
				opt.arg = new_arg("-", opt.arg);
			}
			else
				opt.flag = putflag(opt.flag, argv[e]);
		}
		else
		{
			opt.arg = new_arg(argv[e], opt.arg);
			d = 1;
		}
		e++;
	}
	return (opt);
}
void		show(t_flag flag, t_element *last)
{
	while (last)
	{
		ft_putendl(last->path);
		last = last->prev;
	}
}
char 		*reconstruct_path(char *origin, char *fpath)
{
	char *t;
	char *f;

	f = ft_strjoin(origin, "/");
	t = ft_strjoin(f, fpath);
	free(f);
	return (t);
}
t_element	*build_elist(t_flag flag, char *path)
{
	DIR 		*s;
	t_dirent	*info;
	t_element	*elist;
	t_stat		*sinfo;
	char		*rpath;

	elist = 0;
	if ((s = opendir(path)) == 0)
	{
		perror("ft_ls -> fak");
		return (0);
	}
	while ((info = readdir(s)))
	{
		rpath = reconstruct_path(path, info->d_name);
		if ((sinfo = malloc(sizeof(t_stat))) == 0)
			exit(42);
		if ((stat(rpath, sinfo)) == -1)
			perror(info->d_name);
		else
		{
			if (info->d_name[0] == '.' && flag.all == 1)
				elist = new_element(info->d_name, elist, sinfo);
			else if (info->d_name[0] != '.')
				elist = new_element(info->d_name, elist, sinfo);
		}
	}
	(void)closedir(s);
	return (elist);
}
void		free_element(t_element *l)
{
	t_element *save;

	while (l)
	{	
		if (l->stat)
			free(l->stat);
		save = l;
		l = l->prev;
		free(save);
	}
}

void		lfree_element(t_element *elist)
{
	t_element *tmp;
	if (!elist)
		return ;
	while (elist->next)
	{
		free(elist->path);
		free(elist->stat);
		tmp = elist;
		elist = elist->next;
		free(tmp);
		ft_putendl("FREEEEEED");
	}
}
void		process_elist(char *bpath, t_flag flag, t_element *elist)
{
	t_dir		*folder;
	char 		*path;
	t_element	*t;

	folder = 0;
	if (elist)
	{
		ft_putstr(bpath);
		ft_putendl(" :");
	}
	while (elist)
	{
		if (S_ISDIR(elist->stat->st_mode) && (ft_strcmp(elist->path, ".") != 0 && ft_strcmp(elist->path, "..") != 0))
			folder = new_dir(elist, folder);
		ft_putendl(elist->path); //long display si flag.l == 1
		if (elist->prev == 0)
			t = elist;
		elist = elist->prev;
	}
	if (folder && flag.recursive == 1)
	{
		while (folder)
		{
			path = reconstruct_path(bpath, folder->dir->path);
			process_elist(path, flag, build_elist(flag, path));
			folder = folder->prev;
		}		
	}
	lfree_element(elist);
}

/*

REVOIR LES LISTES ! GERER DE FACONS BIZARRE
FREE QUELQUE TRUCS ~10Mo pour un ft_ls /Applications c cho !
REFAIRE LA MEME MAIS EN GERER LES LISTES UN PEU MIEUX
*/

void	lfree_arg(t_arg *head)
{
	t_arg *t;
	if (!head)
		return ;
	while (head->next)
	{
		free(head->str);
		t = head;
		head = head->next;
		free(t);
		ft_putendl("FREEEEEEEEED");
	}
}
int main(int argc, char **argv)
{
	t_opt 		opt;
	t_arg 		*arg;
	t_element 	*files;
	t_arg		*temp;
	
	opt = init_opt(argc, argv);
	if (opt.arg)
	{
		while (opt.arg)
		{
			process_elist(opt.arg->str, opt.flag, build_elist(opt.flag, opt.arg->str));	
			if (opt.arg->prev == 0)
				temp = opt.arg;
			opt.arg = opt.arg->prev;
		}
		opt.arg = temp;
	}
	else
		process_elist(".", opt.flag, build_elist(opt.flag, "."));
	lfree_arg(temp);
	exit(0);
}
