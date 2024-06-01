SRCS = main.c ft_split.c utils.c utils2.c utils3.c utils4.c
SRCB = main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_split_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c utils4_bonus.c here_doc_bonus.c
DIR = ./srcs/
BONUS_DIR = ./bonus/
OBJS = $(SRCS:%.c=$(DIR)%.o)
OBJB = $(SRCB:%.c=$(BONUS_DIR)%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = pipex
BONUS_NAME = pipex_bonus

all: $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJB) $(BONUS_DIR)pipex_bonus.h
	$(CC) $(OBJB) $(IFLAGS) -o $(BONUS_NAME) 

$(NAME): $(OBJS) $(DIR)pipex.h
	$(CC) $(OBJS) $(IFLAGS) -o $(NAME) #-g -fsanitize=address

$(DIR)%.o: $(DIR)%.c $(DIR)pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_DIR)%.o: $(BONUS_DIR)%.c $(BONUS_DIR)pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJB)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

work: $(NAME) clean

re: fclean all