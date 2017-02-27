OUT= ft_ls

CFILE= long_display.c use_folder_list.c main.c read_folder.c arg.c arg_list.c miscellaneous.c display.c get.c sort.c
OFILE= $(CFILE:.c=.o)

LIB= libft/libft.a

$(OUT): $(OFILE)
	make -C libft/
	gcc -c $(CFILE) -Wall -Werror -Wextra
	gcc -o $(OUT) -Wall -Werror -Wextra $(OFILE) $(LIB)
all: $(OUT)

re: fclean all

clean: 
	make -C libft clean
	rm -f $(OFILE)
fclean: clean
	make -C libft fclean
	rm -f $(OUT)
	rm -f $(LIB)

