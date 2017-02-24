#include "ft_ls.h"

typedef struct	s_es
{
	t_element *origin;
	t_element *list;
}				t_es;

/*
 *
 *
 *				FONCTION DE TEST AVEC .
 *
 *
 *
 *
 *
 */

t_element 	*create_element(void)
{
	t_element *new;

	if ((new = malloc(sizeof(t_element))) == 0)
		exit(42);
	new->name = 0;
	new->path = 0;
	new->stat = 0;
	new->next = 0;
	return (new);
}
t_element		*data_to_element(char *base, t_element *obj, char *name, t_stat *stat)
{
	char 		*tmp;

	obj->name = ft_strdup(name);
	tmp = ft_strjoin(base, "/");
	obj->path = ft_strjoin(tmp, name);
	free(tmp);
	obj->stat = stat;
	obj->next = create_element();
	return (obj->next);
}
t_element *create_list(char *path, int hidden)
{
	t_es 		list;
	t_dirent 	*dir;
	t_stat		*s;
	DIR	 		*folder;

	folder = opendir(path);
	list.list = create_element();
	list.origin = list.list;
	while ((dir = readdir(folder)))
	{
		if ((s = malloc(sizeof(t_stat))) == 0 || lstat(dir->d_name, s) == -1)
		{
			perror("ft_ls");
			free(s);
		}
		else if ((dir->d_name[0] == '.' && hidden) || dir->d_name[0] != '.')
			list.list = data_to_element(path, list.list, dir->d_name, s);
		else
			free(s);
	}
	(void)closedir(folder);
	return (list.origin);
}
t_element *create_dlist(t_element *flist)
{
	t_element 	*save;
	t_es 		list;

	save = flist;
	list.list = create_element();
	list.origin = list.list;
	while (save->next)
	{
		if (S_ISDIR(save->stat->st_mode) && ft_strcmp(".", save->name) != 0 && ft_strcmp("..", save->name) != 0)
		{
			list.list->name = ft_strdup(save->name);
			list.list->path = ft_strdup(save->path);
			list.list->stat = malloc(sizeof(t_stat));
			lstat(list.list->path, list.list->stat);
			list.list->next = create_element();
			list.list = list.list->next;
		}
		save = save->next;
	}
	return (list.origin);
}
void	wfree_element(t_element *hlist)
{
	t_element *tmp;

	while (hlist->next)
	{
		free(hlist->name);
		free(hlist->path);
		free(hlist->stat);
		tmp = hlist;
		hlist = hlist->next;
		free(tmp);
	}
	free(hlist);
}
void	showfile(t_element *hflist, uint8_t ld)
{
	t_element *save;

	save = hflist;
	while (save->next)
	{
		if (ld == 0)
			ft_putendl(save->name);
		save = save->next;
	}
}
int main(int argc, char **argv)
{
	t_element *hlist;
	t_element *hdlist;
	t_element *hdslist;

	if (argc != 2)
		return (0);
	hdslist = hdlist;
	hlist = create_list(argv[1], 0);
	hdlist = create_dlist(hlist);
	wfree_element(hlist);
	wfree_element(hdlist);
	while (1);
	return (0);
}
