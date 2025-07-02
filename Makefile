NAME 		:= cub3D
MLX_DIR		:= ./MLX42
MLX_AR		:= ./MLX42/build/libmlx42.a
LIBFT_PATH 	:= incl/libft_plus/

ifeq ($(shell uname), Linux)
	LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
endif
ifeq ($(shell uname), Darwin)
	LIB = $(MLX_DIR)/build/libmlx42.a -L/opt/homebrew/lib -lglfw \
	-framework Cocoa -framework OpenGL -framework IOKit
endif

SOURCES			:=	srcs/main.c \
					srcs/graphics.c \
					srcs/raycasting.c \
					srcs/cast_walls.c \
					srcs/check_map.c \
					srcs/extract_game_map.c \
					srcs/ft_error.c \
					srcs/arena/arena.c \
					srcs/arena/arena_next_line.c \
					srcs/arena/arena_setsplit.c \
					srcs/arena/arena_split.c \
					srcs/arena/arena_utils.c \
					srcs/utils/flood_fill.c \
					srcs/utils/parsing_utils.c \
					srcs/utils/utils.c \

OBJECTS			:= $(SOURCES:.c=.o)
HEADERS			:= -I ./incl -I $(MLX_DIR)/include

CC 				:= cc
CFLAGS	:= -Wall -Wextra -Werror -I./incl
DEBUG_FLAGS		:= -g #-fsanitize=address -fsanitize=undefined

all: $(NAME)

$(MLX_AR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "\033[36m-----cloning MLX42-----\033[0m"; \
		git clone git@github.com:codam-coding-college/MLX42.git; \
	fi
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4; \

$(NAME): $(MLX_AR) $(OBJECTS)
	@echo "\033[36m-----making libft-----\033[0m"
	@make -C $(LIBFT_PATH)
	$(CC) $(OBJECTS) $(LIBFT_PATH)libft_plus.a \
		$(HEADERS) $(LIB) -o $(NAME)

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(MLX_DIR)/build
	@make clean -C $(LIBFT_PATH)
	@echo "\033[36m-----headers removed-----\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@rm -rf $(MLX_DIR)
	@echo "\033[36m-----everything cleaned-----\033[0m"

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug