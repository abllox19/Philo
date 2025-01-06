#VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore.txt

#test:
#	$(VALGRIND) ./votre_executable
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -g3 -lreadline

# Paths
SRC_PATH = src/
OBJ_PATH = obj/
LIBFT_PATH = libft/

# Libraries and flags
LIBFT = $(LIBFT_PATH)libft.a

# Source files
PHILO_SRC = main.c init.c ft_isdigit.c

# Object files
PHILO_OBJS = $(addprefix $(OBJ_PATH), $(PHILO_SRC:.c=.o))

# Output
PHILO_NAME = philo

# Rules
all: $(LIBFT) $(PHILO_NAME)

# Build the binary
$(PHILO_NAME): $(PHILO_OBJS) $(LIBFT)
	$(MAKE) -C $(LIBFT_PATH)  # Compile libft if necessary
	$(CC) $(CFLAGS) $(PHILO_OBJS) $(LIBFT) $(LDFLAGS) -o $(PHILO_NAME) -g3

# Build the object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH) # Create obj directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

# Cleaning rules
clean:
	$(RM) -r $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(PHILO_NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
