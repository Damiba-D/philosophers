NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM			= rm -f

# Source files
SRCS		= philo.c \
			  parsing.c \
			  print_utils.c \
			  utils.c \
			  utils2.c \
			  cleanup.c \
			  initializing.c \
			  philo_actions.c \
			  # Add more .c files here as you create them

# Object files
OBJS		= $(SRCS:.c=.o)

# Colors for pretty output
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ philo compiled successfully$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓ Compiled: $<$(RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "$(RED)✗ Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)✗ Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re