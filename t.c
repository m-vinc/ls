#include "ft_ls.h"

char *ft_strjoinf(char *src, char *dest)
{
	char *t;
	
	t = src;
	src = ft_strjoin(src, dest);
	if (t)
		free(t);
	return (src);
}

int main()
{
	char * e;
	e = malloc(2);
	e[0] = 'q';
	e[1] = '\0';
	e = ft_strjoinf(e, " fak");
	while (1);
}
