NAME    = philo

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -O3
SRCS    =	srcs/aux.c srcs/aux2.c srcs/main.c \
			srcs/verify.c srcs/routines.c \
			srcs/initers.c
OBJDIR  = output
OBJS    = $(patsubst srcs/%.c,$(OBJDIR)/%.o,$(SRCS))

INC     = -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)

$(OBJDIR)/%.o: srcs/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
	clear

v: re
	clear
	valgrind --tool=helgrind -s ./$(NAME) 5 800 200 200

r: re
	clear
	valgrind --tool=helgrind -s ./$(NAME)

.PHONY: all clean fclean re v
