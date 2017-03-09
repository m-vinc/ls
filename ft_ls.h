/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:16:06 by vmorvan           #+#    #+#             */
/*   Updated: 2017/03/09 23:49:18 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

typedef struct	s_flag
{
	uint8_t recursive;
	uint8_t rsort;
	uint8_t all;
	uint8_t ld;
	uint8_t time;
	uint8_t	size;
	uint8_t	nosort;
	uint8_t	accesstime;
	uint8_t	nocontent;
}				t_flag;
typedef struct	s_arg
{
	char			*str;
	char			*path;
	struct s_arg	*next;
}				t_arg;
typedef struct	s_opt
{
	t_flag		flag;
	t_arg		*arg;
}				t_opt;
typedef struct	s_el
{
	char			*name;
	t_stat			*stat;
	char			*path;
	struct s_el		*next;
}				t_element;
typedef struct	s_es
{
	t_element *origin;
	t_element *list;
}				t_es;
typedef struct	s_as
{
	t_arg		*origin;
	t_arg		*list;
}				t_as;
typedef struct	s_max
{
	int			linkmax;
	int			sizemax;
	int			daymax;
	int			majormax;
	int			minormax;
	int			grpmax;
	uint8_t		mode;
}				t_max;

/* ----------------ARG.C - arg------------------------- */
t_flag			zflag();
t_opt			init_flag(int argc, char **argv);
t_flag			putflag(t_flag flag, char *arg);
/* ----------------ARG_LIST.C-------------------------- */
t_arg			*create_arg();
t_arg			*data_to_arg(char *str, t_arg *obj);
void			wfree_arg(t_arg *harg);
/* ----------------READ_FOLDER.C - file---------------- */
t_element		*create_element(void);
t_element		*data_to_element(char *base,
		t_element *obj, char *name,
		t_stat *stat);
t_element		*create_list(char *path, int hidden);
t_element		*create_dlist(t_element *file);
void			wfree_element(t_element *hlist);
/* ----------------MISCELLANEOUS.C--------------------- */
int				element_length(t_element *hlist);
int				arg_length(t_arg *hlist);
char			*ft_strjoinf(char *src, char *dest);
char			*build_path(char *base, char *name);
char			*get_majorminor(t_element *element);
/* ----------------MISCELLEANEOUS_1.C---------------------*/
t_es			init_list();
t_as			init_arglist();
void			w_error(t_stat **s, char *url);
t_max			zmax();
t_flag			another_flag(char x, t_flag flag);
/* ----------------DISPLAY.C--------------------------- */
void			addtime(char **time, char **f);
void			showdetail(t_element *element, t_flag flag, t_max max);
int				showfile(t_element *hflist, t_flag flag, int f_showsize);
void			w_perror(char *str);
t_max			init_max(t_element *element);
/* ----------------GET.C------------------------------- */
t_element		*get_argtofile(t_arg *hlist, t_flag flag, int *n);
t_element		*get_argtofolder(t_arg *hlist);
t_max			getmajminmax(t_max max, t_element *element);
t_max			getgroupmax(t_max max, t_element *element);
t_max			getsizemax(t_max max, t_element *element);
/* ----------------SORT.C------------------------------ */
t_element		*sortlexico(t_element *hlist);
t_element		*sortreverse(t_element *hlist);
void			swap_edata(t_element *un, t_element *deux);
t_element		*sort(t_element *hlist, t_flag flag);
t_element		*sortsize(t_element *hlist);
/* ----------------SORT_1.C----------------------------- */
t_element		*sorttime(t_element *hlist);
t_element		*sorttime_u(t_element *hlist);
/* ----------------USE_FOLDER_LIST.C-------------------- */
void			show_flist(int x, t_element *folder, t_opt opt);
/* ----------------LONG_DISPLAY.C----------------------- */
void			showfirst(t_element *element, char **f);
void			showright(t_element *element, char **f);
void			shownumberinfo(t_element *element, char **f, t_max max);
void			showtime(t_element *element, char **f, t_flag flag);
void			showislink(t_element *element, char **f);
/* ----------------LONG_DISPLAY_1.C-----------------------*/
void			showsize(t_element *hfile);
/* ----------------PADDING.C----------------------------- */
void			padding(char *data, char **str, t_max max,
		t_element *element);
void			padding_mm(t_element *element, t_max max, char **str);
void			padding_grp(char *gr_name, t_max max, char **str);
#endif
