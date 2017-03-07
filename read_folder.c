/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:19:04 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/07 22:10:19 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_element		*create_element(void)
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

t_element		*data_to_element(char *base, t_element *obj,
		char *name, t_stat *stat)
{
	char	*tmp;

	obj->name = ft_strdup(name);
	if (base)
	{
		tmp = ft_strjoin(base, "/");
		obj->path = ft_strjoin(tmp, name);
		free(tmp);
	}
	else
		obj->path = 0;
	obj->stat = stat;
	obj->next = create_element();
	return (obj->next);
}

t_element		*create_list(char *path, int hidden)
{
	t_es		list;
	t_dirent	*dir;
	t_stat		*s;
	DIR			*folder;
	char		*url;

	if ((folder = opendir(path)) == 0)
	{
		w_perror(path);
		return (0);
	}
	list = init_list();
	while ((dir = readdir(folder)))
	{
		url = build_path(path, dir->d_name);
		if ((s = malloc(sizeof(t_stat))) == 0 || lstat(url, s) == -1)
			w_error(&s);
		else if ((dir->d_name[0] == '.' && hidden) || dir->d_name[0] != '.')
			list.list = data_to_element(path, list.list, dir->d_name, s);
		else
			free(s);
		free(url);
	}
	(void)closedir(folder);
	return (list.origin);
}

t_element		*create_dlist(t_element *flist)
{
	t_element	*save;
	t_es		list;

	save = flist;
	list.list = create_element();
	list.origin = list.list;
	while (save->next)
	{
		if (S_ISDIR(save->stat->st_mode) &&
				ft_strcmp(".", save->name) != 0 &&
				ft_strcmp("..", save->name) != 0)
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

void			wfree_element(t_element *hlist)
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
