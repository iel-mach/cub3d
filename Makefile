# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 23:29:53 by iel-mach          #+#    #+#              #
#    Updated: 2022/07/28 19:59:03 by iel-mach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC = ./src/*.c ./utils/*.c
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
MLX = -lmlx -framework OpenGL -framework AppKit
CC = cc

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(FLAGS) $(SRC) $(MLX) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all