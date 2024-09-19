S = src
BUILD = build

# Use the shell find command to gather all .c files recursively from $(S)
SRCS = $(shell find $(S) -name "*.c")

# Convert the .c files into corresponding .o files in the build/ directory
OBJS = $(patsubst $(S)/%.c,$(BUILD)/%.o,$(SRCS))

# Compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror -Iinc -I./libft -Imlx

# MLX and libft configuration
MLX_LIB = mlx/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

TARGET = Cub3D

# Colors for output
BLUE = \033[34m
YELLOW = \033[33m
GREEN = \033[32m
WHITE = \033[0m

all: $(TARGET)

# Build libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Build the final target
$(TARGET): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -O3 -o $(TARGET) $(OBJS) $(MLX_LIB) $(LIBFT)
	printf "$(GREEN)Compilation finished\n$(WHITE)"

# Compile object files
$(BUILD)/%.o: $(S)/%.c | $(BUILD) $(DIRS)
	mkdir -p $(dir $@)        # Create the necessary subdirectories
	$(CC) $(FLAGS) -c $< -o $@
	printf "$(BLUE)> Compiled: $<$(WHITE)\n"

# Create the build directory structure (subdirs)
$(BUILD):
	mkdir -p $(BUILD)

# Clean object files
clean:
	rm -f $(OBJS)
	printf "$(YELLOW)Object files removed$(WHITE)\n"

# Full clean (including target and build directory)
fclean: clean
	rm -rf $(TARGET)
	rm -rf $(BUILD)
	printf "$(YELLOW)Directory cleaned$(WHITE)\n"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
.SILENT:

