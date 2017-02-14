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
	struct	s_arg	*prev;
	struct 	s_arg 	*next;
}		t_arg;
typedef struct	s_opt
{
	t_flag 	flag;
	t_arg 	*arg;
}		t_opt;
typedef struct	s_el
{
	char 		*path;
	t_stat		*stat;
	struct	s_el	*prev;
	struct 	s_el 	*next;
}		t_element;
typedef struct	s_dir
{
	t_element	*dir;
	struct	s_dir	*next;
	struct	s_dir	*prev;
}		t_dir;
#endif
