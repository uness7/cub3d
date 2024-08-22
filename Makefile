S = src
BUILD = build
SRCS = $(S)/main.c \

INCS = inc
CC = cc

FLAGS = -Wall -Wextra -Werror
TARGET = cub3D
OBJS = $(SRCS:$(S)/%.c=$(BUILD)/%.o)

BLUE = \033[34m
YELLOW = \033[33m
GREEN = \033[32m
WHITE = \033[0m

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)
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

