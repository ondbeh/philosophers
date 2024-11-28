# Name of the library
NAME		=	philo

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Wunreachable-code -pthread -I.
DEBUG_FLAGS	=	-g  -fsanitize=thread -fcolor-diagnostics -fansi-escape-codes
RM			=	rm -f
INCLUDES	=	-I .

# Directories
SRC_DIR		=	src
OBJ_DIR		=	obj

# Source files and corresponding object files
SRCS		=	main.c main_utils.c error_handler.c mutex_utils.c philo_routine.c philo_routine_utils.c \
				observer_routine.c

SRCS		:=	$(addprefix $(SRC_DIR)/, $(SRCS))
OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

# Link object files and libft to create the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Compiling philo project"

debug: $(OBJS)
	@$(CC) $(DEBUG_FLAGS) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Compiling philo project with debug flags"

docekr: $(OBJS)
	@$(CC) -g $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Compiling philo project with debug flags"

# Compile source files into object files in the obj/ folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create the obj/ directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Creating folder for object files"

# Clean object files from both fdf and libft
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Deleting philo objects"

# Full clean: also remove the executable and libft objects
fclean: clean
	@$(RM) $(NAME)
	@echo "Deleting philo executable"

# Rebuild everything
re: fclean all

# Norm rule
norm:
	@echo "Norminette for philo.h and src:"
	@-norminette src philo.h || true

# PHONY prevents conflicts with files named like the targets
.PHONY: all clean fclean re
