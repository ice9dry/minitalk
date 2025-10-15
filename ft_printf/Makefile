# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar
ARFLAGS	= rcs

# Directories
OBJ_DIR	= objs
LIBFT_DIR = ./libft

# Target
NAME = libftprintf.a
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
LIB_SRCS = ft_printf.c ft_nbrlen.c ft_putchar.c ft_putstr.c ft_putnbr.c \
	ft_print_pointer.c ft_puthex.c ft_handle_specifier.c

# Objects
LIB_OBJS = $(addprefix $(OBJ_DIR)/, $(LIB_SRCS:.c=.o))

# Default target
all: makelibft $(NAME)

# Build static library
$(NAME): $(LIB_OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	$(AR) $(ARFLAGS) $@ $(wildcard $(OBJ_DIR)/*.o)

makelibft:
	@$(MAKE) -C $(LIBFT_DIR)

# Create object directory
$(OBJ_DIR):
	mkdir -p $@

# Compile library objects
$(OBJ_DIR)/%.o: %.c ft_printf.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

# Clean everything including library
fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(EXEC)

# Rebuild everything
re: fclean all

.PHONY: all bonus clean fclean re makelibft
