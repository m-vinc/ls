NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m

NAME= ft_ls

CFILE= miscellaneous_1.c \
long_display_1.c \
padding.c \
long_display.c \
use_folder_list.c \
main.c \
read_folder.c \
arg.c \
arg_list.c \
miscellaneous.c \
display.c  \
get.c \
sort.c \
sort_1.c

OFILE= $(CFILE:.c=.o)

LIB= libft/libft.a

all: $(CFILE) $(NAME)

$(NAME): $(OFILE)
	@echo "${WARN_COLOR}Ft_ls:${NO_COLOR} ${OK_COLOR}Compile libft${NO_COLOR}"
	@make -C libft/
	@gcc -o $@ $(OFILE) -Wall -Wextra -Werror $(LIB)
	@echo "${WARN_COLOR}Ft_ls:${NO_COLOR} Compile -> $(NAME)${OK_COLOR} OK ${NO_COLOR}"
.c.o:
	@echo "${WARN_COLOR}Ft_ls:${NO_COLOR} Compile -> ${WARN_COLOR}$<${NO_COLOR} => ${OK_COLOR} $@ ${NO_COLOR}"
	@gcc -c $< -o $@ -Wall -Werror -Wextra
clean:
	@echo "${WARN_COLOR}Ft_ls:${NO_COLOR} ${ERROR_COLOR}Delete ${NO_COLOR}-> objects files."
	@make -C libft/ clean
	@rm -f $(OFILE)
fclean: clean
	@echo "${WARN_COLOR}Ft_ls:${NO_COLOR} ${ERROR_COLOR}Delete${NO_COLOR} -> $(NAME)"
	@make -C libft/ fclean
	@rm -f $(NAME)
re: fclean $(NAME) 
