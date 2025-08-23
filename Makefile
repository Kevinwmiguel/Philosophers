NAME    = philosophers

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -g

SRCS    = $(wildcard srcs/*.c)
OBJDIR  = output
OBJS    = $(patsubst srcs/%.c,$(OBJDIR)/%.o,$(SRCS))

INC     = -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)
	@bash ./loadbar.sh

# regra para compilar .o dentro da pasta output/
$(OBJDIR)/%.o: srcs/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
	@bash ./loadbar.sh
	clear

v: re
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes ./$(NAME)

r: re
	clear
	valgrind --tool=helgrind -s ./$(NAME)

.PHONY: all clean fclean re v
