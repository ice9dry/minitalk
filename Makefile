# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar
ARFLAGS	= rcs

# Directories
OBJ_DIR	= objs
OBJ_BONUS_DIR = objs_bonus
SRC_DIR = src
INC_DIR = include
FT_PRINTF_DIR = ft_printf

# Target
SERVER_NAME = server
CLIENT_NAME = client

# Source files
SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_BONUS_SRC = server_bonus.c
CLIENT_BONUS_SRC = client_bonus.c

# Header files
#HEADER_NAMES = server.h client.h
#HEADER_NAMES = #server_bonus.h client_bonus.h
HEADERS = ./include/server.h ./include/client.h $(FT_PRINTF_DIR)/ft_printf.h $(FT_PRINTF_DIR)/libft/libft.h
HEADERS_BONUS = ./include/server_bonus.h ./include/client_bonus.h $(FT_PRINTF_DIR)/ft_printf.h $(FT_PRINTF_DIR)/libft/libft.h

# Objects
SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:.c=.o))
CLIENT_OBJ = $(addprefix $(OBJ_DIR)/, $(CLIENT_SRC:.c=.o))
SERVER_BONUS_OBJ = $(addprefix $(OBJ_BONUS_DIR)/, $(SERVER_BONUS_SRC:.c=.o))
CLIENT_BONUS_OBJ = $(addprefix $(OBJ_BONUS_DIR)/, $(CLIENT_BONUS_SRC:.c=.o))

# Default target: build library without bonus
all: makeprintf $(SERVER_NAME) $(CLIENT_NAME)

# Build objects
$(SERVER_NAME): $(SERVER_OBJ) $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $^ -o $@ -L$(FT_PRINTF_DIR) -lftprintf

$(CLIENT_NAME): $(CLIENT_OBJ) $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $^ -o $@ -L$(FT_PRINTF_DIR) -lftprintf

# With bonus
bonus: .bonus

.bonus: ./src/server_bonus.c ./src/client_bonus.c $(HEADERS_BONUS)
	@$(MAKE) makeprintf 
	@$(MAKE) $(SERVER_NAME)_bonus 
	@$(MAKE) $(CLIENT_NAME)_bonus
	@touch .bonus

$(SERVER_NAME)_bonus: $(SERVER_BONUS_OBJ) $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $^ -o server -L$(FT_PRINTF_DIR) -lftprintf

$(CLIENT_NAME)_bonus: $(CLIENT_BONUS_OBJ) $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $^ -o client -L$(FT_PRINTF_DIR) -lftprintf

debug: CFLAGS += -g
debug: fclean
debug: all

makeprintf:
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_BONUS_DIR):
	mkdir -p $@

# Compile library objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJ_BONUS_DIR)/%_bonus.o: $(SRC_DIR)/%_bonus.c $(HEADERS_BONUS) | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

norm:
	@norminette $(SRC_DIR) $(INC_DIR) $(FT_PRINTF_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

# Clean object and executable files
fclean: clean
	rm -rf $(FT_PRINTF_DIR)/libftprintf.a
	rm -rf $(FT_PRINTF_DIR)/libft/libft.a
	rm -rf $(SERVER_NAME)
	rm -rf $(CLIENT_NAME)
	rm -rf .bonus

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re makeprintf norm debug bonus
