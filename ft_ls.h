/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorvan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:16:06 by vmorvan           #+#    #+#             */
/*   Updated: 2017/02/26 18:05:41 by vmorvan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H
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
typedef struct	stat	t_stat;
typedef struct	dirent	t_dirent;

typedef struct	s_flag
{
	uint8_t recursive;
	uint8_t rsort;
	uint8_t all;
	uint8_t ld;
	uint8_t time;
}		t_flag;
typedef struct	s_arg
{
	char 		*str;
	char		*path;
	struct 	s_arg 	*next;
}		t_arg;
typedef struct	s_opt
{
	t_flag 	flag;
	t_arg 	*arg;
}				t_opt;
typedef struct	s_el
{
	char 		*name;
	t_stat		*stat;
	char 		*path;
	struct 	s_el 	*next;
}		t_element;

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
/* ----------------ARG.C - arg------------------------- */
t_flag	zflag();
t_opt	init_flag(int argc, char **argv);
t_flag	putflag(t_flag flag, char *arg);
/* ----------------ARG_LIST.C-------------------------- */
t_arg	*create_arg();
t_arg	*data_to_arg(char *str, t_arg *obj);
void	wfree_arg(t_arg *harg);
/* ----------------READ_FOLDER.C - file---------------- */
t_element	*create_element(void);
t_element	*data_to_element(char *base, t_element *obj, char *name, t_stat *stat);
t_element	*create_list(char *path, int hidden);
t_element	*create_dlist(t_element *file);
void		wfree_element(t_element *hlist);
/* ----------------MISCELLANEOUS.C--------------------- */
int			element_length(t_element *hlist);
int			arg_length(t_arg *hlist);
/* ----------------DISPLAY.C--------------------------- */
int			showfile(t_element *hflist, uint8_t ld);
void		w_perror(char *str);
/* ----------------GET.C------------------------------- */
t_element	*get_argtofile(t_arg *hlist);
t_element	*get_argtofolder(t_arg *hlist);
/* ----------------SORT.C------------------------------ */
t_element	*sortlexico(t_element *hlist);
t_element	*sortreverse(t_element *hlist);
void		swap_edata(t_element *un, t_element *deux);
t_element	*sort(t_element *hlist, t_flag flag);
#endif
