NAME    = philosophers

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -g

SRCS    = $(wildcard srcs/*.c)
OBJS    = $(SRCS:.c=.o)

INC     = -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)
	@bash ./loadbar.sh

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	@bash ./loadbar.sh
	clear

v: re
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes ./$(NAME)

rc: re
	clear
	valgrind --tool=helgrind -s ./$(NAME)

.PHONY: all clean fclean re v

