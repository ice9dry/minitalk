# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar
ARFLAGS	= rcs

# Directories
OBJ_DIR	= objs

# Target
NAME = libft.a

# Source files
LIB_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	ft_substr.c ft_strjoin.c ft_strrchr.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_atof.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# Objects
LIB_OBJS	= $(addprefix $(OBJ_DIR)/, $(LIB_SRCS:.c=.o))

# Default target: build library without bonus
all: $(NAME)

# Build static library
$(NAME): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Create object directory
$(OBJ_DIR):
	mkdir -p $@

# Compile library objects
$(OBJ_DIR)/%.o: %.c libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything including library
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all bonus clean fclean re
