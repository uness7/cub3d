S = src

BUILD = build

SRCS = $(wildcard $(S)/*.c)

CC = cc

FLAGS = -Wall -Wextra -Werror -Iinc -Imlx

TARGET = Cub3D

OBJS = $(SRCS:$(S)/%.c=$(BUILD)/%.o)

# Paths to the libraries

MLX_DIR = mlx
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lXrandr -lm


# Colors
BLUE = \033[34m
YELLOW = \033[33m
GREEN = \033[32m
WHITE = \033[0m

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -I/usr/include -Imlx -O3 -o $(TARGET) $(OBJS) $(MLX_LIB)
	printf "$(GREEN)Compilation finished\n$(WHITE)"

$(BUILD)/%.o: $(S)/%.c | $(BUILD)
	$(CC) $(FLAGS) -c $< -o $@
	printf "$(BLUE)> $<$(WHITE)\n"

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -f $(OBJS)
	printf "$(YELLOW)Object files removed$(WHITE)\n"

fclean: clean
	rm -rf $(TARGET)
	rm -rf $(BUILD)
	printf "$(YELLOW)Directory is cleaned$(WHITE)\n"

re: fclean all

.PHONY: all clean fclean re

.SILENT: 

