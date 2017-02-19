OUT= ft_ls

CFILE= ft_ls.c
OFILE= $(CFILE:.c=.o)

LIB= libft/libft.a

$(OUT): $(OFILE)
	make -C libft/
	gcc -o $(OUT) -Wall -Werror -Wextra $(OFILE) $(LIB) -fsanitize=address
all: $(OUT)

re: fclean all

clean: 
	make -C libft clean
	rm -f $(OFILE)
fclean: clean
	make -C libft fclean
	rm -f $(OUT)
	rm -f $(LIB)

