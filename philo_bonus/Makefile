NAME = philo_bonus

HEADER = ./inc/

SRCS = philo.c init.c do_routine.c write_message.c error_and_free.c utils.c

OBJSDIR = ./objs
SRCSDIR = ./srcs
HDRDIR = ./inc


CC = gcc

FLAGS = -Wall -Werror -Wextra -g

OBJS = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HDRDIR) -c $< -o $@


$(NAME): $(OBJSDIR) $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
