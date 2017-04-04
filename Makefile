# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: behamon <behamon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/21 16:01:32 by behamon           #+#    #+#              #
#    Updated: 2017/02/21 16:01:35 by behamon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

NAME	= wolf3d

NOC		=\033[0m
OKC		=\033[32m
ERC		=\033[31m
WAC		=\033[33m

SRC		= src/file_loader.c \
		  src/wolf_init.c \
		  src/wolf_main.c \
		  src/utilities.c \
		  src/hooks_mvt.c \
		  src/color_and_draw.c \
		  src/dda_functions.c \
		  src/hooks_tools.c \
		  src/check_file.c \
		  src/raycasting.c

OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))

FLAGS 	= -Wall -Werror -Wextra -O3
MLX_FLAGS = -framework OpenGL -framework AppKit -lmlx

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(FLAGS) -L./libft/ -lft -I./ $(MLX_FLAGS) $(SRC) -o $(NAME)
	@echo "$(OKC)Wolf3D\t: Binary Compilation.. Done$(NOC)"

obj/%.o: src/%.c
	@mkdir -p obj
	@gcc $(FLAGS) -I./ -c $< -o $@

clean:
	@rm -rf obj/
	@make -C libft/ clean
	@echo "$(OKC)Wolf3D\t: Cleaning.. Done$(NOC)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@echo "$(OKC)Wolf3D\t: Full Clean.. Done$(NOC)"

re: fclean all

all: $(NAME)
