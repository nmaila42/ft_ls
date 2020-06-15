NAME = ft_ls
LIB	= libft/libft.a
RUN = ft_ls.a
EXE = ft_ls
CC = gcc
FLAG = -Wall -Werror -Wextra
ARC = ar rc
SRC = print.c recurse.c main.c sort.c
OBJ = print.o recurse.o main.o sort.o

all: $(NAME)

$(NAME): 
	@echo "\033[0;94m <<<<<<Compiling $(NAME)>>>>>> \033[0m"
		@make -C libft/
		$(CC) -c $(FLAG) $(SRC) 
		$(ARC) $(RUN) $(OBJ) 
		$(CC) $(FlAGS) $(RUN) $(LIB) -o $(NAME)
		
	@echo "\033[0;94m <<<<<<<ft_ls compiled>>>>>>>\33[0m"
	
clean:	
	@/bin/rm -f $(OBJ)
	@make -C ./libft/ clean
	@echo "\033[0;94m <<<<<<< OBJ files removed >>>>>>>\33[0m"
fclean: clean

	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(RUN)
	make -C ./libft/ fclean
	@echo "\033[0;94m <<<< $(RUN) & $(NAME) cleared >>>><<<< make to compile again >>>>\33[0m"


re: fclean all
