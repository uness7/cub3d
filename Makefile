S = src
BUILD = build
SRCS = $(shell find $(S) -name "*.c")
OBJS = $(patsubst $(S)/%.c,$(BUILD)/%.o,$(SRCS))
CC = cc
FLAGS = -Wall -Wextra -Werror -Iinc -I./libft -Imlx -g3

MLX_LIB = mlx/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

TARGET = cub3D

BLUE = \033[34m
YELLOW = \033[33m
GREEN = \033[32m
WHITE = \033[0m

all: $(TARGET)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(TARGET): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -O3 -o $(TARGET) $(OBJS) $(MLX_LIB) $(LIBFT)
	printf "$(GREEN)Compilation finished\n$(WHITE)"

$(BUILD)/%.o: $(S)/%.c | $(BUILD) $(DIRS)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@
	printf "$(BLUE)> Compiled: $<$(WHITE)\n"

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -f $(OBJS)
	printf "$(YELLOW)Object files removed$(WHITE)\n"

fclean: clean
	rm -rf $(TARGET)
	rm -rf $(BUILD)
	printf "$(YELLOW)Directory cleaned$(WHITE)\n"

re: fclean all

.PHONY: all clean fclean re
.SILENT:

