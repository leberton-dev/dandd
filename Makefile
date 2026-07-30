NAME 	:=dandd
SRCS 	:= src/main.c
OBJSDIR := build
OBJS 	:= $(patsubst src/%.c,$(OBJSDIR)/%.o,$(SRCS))
HEADERS := ""

CC 		:= cc
INCLUDE := -I./include
CFLAGS	:= -Wall -Wextra -Werror -lraylib

RM		:= rm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(OBJSDIR)/%.o: src/%.c $(HEADER) | $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) -rf $(OBJSDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
