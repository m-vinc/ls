/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:13:53 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/28 12:29:53 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	showfirst(t_element *element, char **f)
{
	if (S_ISREG(element->stat->st_mode))
		*f = ft_strjoinf(*f, "-");
	if (S_ISDIR(element->stat->st_mode))
		*f = ft_strjoinf(*f, "d");
	if (S_ISCHR(element->stat->st_mode))
		*f = ft_strjoinf(*f, "c");
	if (S_ISBLK(element->stat->st_mode))
		*f = ft_strjoinf(*f, "b");
	if (S_ISFIFO(element->stat->st_mode))
		*f = ft_strjoinf(*f, "p");
	if (S_ISLNK(element->stat->st_mode))
		*f = ft_strjoinf(*f, "l");
	if (S_ISSOCK(element->stat->st_mode))
		*f = ft_strjoinf(*f, "s");
	if (S_ISWHT(element->stat->st_mode))
		*f = ft_strjoinf(*f, "D");
}
void	showright(t_element *element, char **f)
{
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IRUSR) ? "r" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IWUSR) ? "w" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IXUSR) ? "x" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IRGRP) ? "r" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IWGRP) ? "w" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IXGRP) ? "x" : "-");
	*f = ft_strjoinf(*f ,(element->stat->st_mode & S_IROTH) ? "r" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IWOTH) ? "w" : "-");
	*f = ft_strjoinf(*f, (element->stat->st_mode & S_IXOTH) ? "x " : "- ");
}
void	shownumberinfo(t_element *element, char **f)
{
	char *tmp;
	struct passwd *pwd;
	struct group *grp;

	grp = getgrgid(element->stat->st_gid);
	pwd = getpwuid(element->stat->st_uid);
	tmp =  ft_itoa(element->stat->st_nlink);
	*f = ft_strjoinf(*f, tmp);
	free(tmp);
	*f = ft_strjoinf(*f, "\t");
	*f = ft_strjoinf(*f, pwd->pw_name);
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, grp->gr_name);
	*f = ft_strjoinf(*f, "\t");
	tmp = (S_ISCHR(element->stat->st_mode) || 
			S_ISBLK(element->stat->st_mode) ? 
			get_majorminor(element) : 
			ft_itoa(element->stat->st_size));
	*f = ft_strjoinf(*f,tmp);
	free(tmp);
	*f = ft_strjoinf(*f, "\t");
}
void	showtime(t_element *element, char **f)
{
	char 	**time;
	int 	e;
	char 	**s;
	char 	**hour;


	e = 0;
	time = ft_strsplit(ctime(&element->stat->st_ctime), ' ');
	*f = ft_strjoinf(*f, time[1]);
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, time[2]);
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

void	showislink(t_element *element, char **f)
{
	char 	rl[1024];
	int 	size;
	
	size = readlink((element->path ? 
				element->path : element->name), rl, 1024);
	rl[size] = '\0';
	*f = ft_strjoinf(*f, " ");
	*f = ft_strjoinf(*f, "-> ");
	*f = ft_strjoinf(*f, rl);
}
