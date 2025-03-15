# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:35:06 by cesasanc          #+#    #+#              #
#    Updated: 2024/11/08 14:27:52 by cesasanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
BONUS_NAME	= cub3d_bonus
CC 			= cc

FLAGS 		= -Wall -Wextra -Werror
MLX42 		= ./MLX42/build/libmlx42.a

SRC_DIR 	= ./sources
BONUS_DIR	= ./bonus
OBJ_DIR		= ./obj/
LIBFT		= ./libft/

FILES		= main.c \
			map_init.c \
			win_init.c \
			colors.c \
			parse_map.c \
			parsing.c \
			textures.c \
			utils.c \
			render.c \
			raycast.c \
			hooks.c \
			exit_utils.c  \
			movement.c

BONUS_FILES = main_bonus.c \
			map_init_bonus.c \
			win_init_bonus.c \
			colors_bonus.c \
			parse_map_bonus.c \
			minimap_bonus.c \
			parsing_bonus.c \
			textures_bonus.c \
			utils_bonus.c \
			utils2_bonus.c \
			render_bonus.c \
			raycast_bonus.c \
			hooks_bonus.c \
			exit_utils_bonus.c  \
			movement_bonus.c \
			minimap_ray_bonus.c \
			doors_bonus.c \
			gun_bonus.c \
			enemy_bonus.c \
			raycast_utils_bonus.c \
			enemy_utils_bonus.c \

MLX42FLAGS = -Iincludes -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

INCLUDES = -I$(SRC_DIR) -I./includes 
		
OBJ_FILES = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

BONUS_OBJ_FILES = $(addprefix $(OBJ_DIR), $(BONUS_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(MLX42): 
	@if [ ! -d "./MLX42" ]; then \
		git clone git@github.com:codam-coding-college/MLX42.git MLX42; \
	fi
	@if [ ! -f "$(MLX42)" ]; then \
		cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

$(NAME): $(MLX42) $(LIBFT)/libft.a $(OBJ_FILES) 
	@echo "Compiling Cub3d..."
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(MLX42) \
		$(MLX42FLAGS) -lm
	@echo "\033[32m Cub3d has been built successfully!\033[0m"

bonus: .bonus

.bonus: $(MLX42) $(LIBFT)/libft.a $(BONUS_OBJ_FILES) 
	@echo "Compiling Cub3d_bonus..."
	@ $(CC) $(FLAGS) -o $(BONUS_NAME) $(BONUS_OBJ_FILES) -L$(LIBFT) -lft $(MLX42) \
		$(MLX42FLAGS) -lm
	@touch .bonus
	@echo "\033[32m Cub3d_bonus has been built successfully!\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c $(SRC_DIR)/cub3d.h | $(OBJ_DIR)
	@echo "Compiling $< to $@"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%_bonus.o: $(BONUS_DIR)/%_bonus.c $(BONUS_DIR)/cub3d_bonus.h | $(OBJ_DIR)
	@echo "Compiling $< to $@"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@


fsanitize: $(MLX42) $(LIBFT)/libft.a $(OBJ_FILES)
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(MLX42) \
		$(MLX42FLAGS) -g -fsanitize=address -static-libsan -lm
	
clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	
fclean: clean
	make fclean -C $(LIBFT)
	rm -f .bonus
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean $(NAME)

rebonus: fclean bonus

.PHONY: all clean fclean re bonus
