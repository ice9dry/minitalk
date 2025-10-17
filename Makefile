# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar
ARFLAGS	= rcs

# Directories
OBJ_DIR	= objs
SRC_DIR = src
INC_DIR = include
FT_PRINTF_DIR = ft_printf

# Target
SERVER_NAME = server
CLIENT_NAME = client

# Source files
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Header files
HEADER_NAMES = server.h client.h
HEADERS = $(patsubst %,$(INC_DIR)/%,$(HEADER_NAMES)) \
	$(FT_PRINTF_DIR)/ft_printf.h $(FT_PRINTF_DIR)/libft/libft.h

# Objects
SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:.c=.o))
CLIENT_OBJ = $(addprefix $(OBJ_DIR)/, $(CLIENT_SRC:.c=.o))

# Default target: build library without bonus
all: makeprintf $(SERVER_NAME) $(CLIENT_NAME)

# Build objects
$(SERVER_NAME): $(SERVER_OBJ) $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $^ -o $@ -L$(FT_PRINTF_DIR) \
	-lftprintf

$(CLIENT_NAME): $(CLIENT_OBJ) $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $^ -o $@ -L$(FT_PRINTF_DIR) \
	-lftprintf

debug: CFLAGS += -g
debug: fclean
debug: all

makeprintf:
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(OBJ_DIR):
	mkdir -p $@

# Compile library objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)| $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

norm:
	@norminette $(SRC_DIR) $(INC_DIR) $(FT_PRINTF_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

# Clean object and executable files
fclean: clean
	rm -rf $(FT_PRINTF_DIR)/libftprintf.a
	rm -rf $(SERVER_NAME)
	rm -rf $(CLIENT_NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re makeprintf norm debug
