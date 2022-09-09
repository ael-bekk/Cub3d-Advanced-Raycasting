NAME	= cub3d

SRCS	= cub3d.c \
		utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strjoin.c utils/ft_split.c utils/ft_memcpy.c utils/ft_substr.c utils/ft_strchr.c utils/get_next_line.c utils/ft_isdigit.c utils/ft_atoi.c src/init_args.c \
		utils/ft_lst_new.c utils/ft_lst.c \
		src/parsing.c utils/ft_strnstr.c utils/ft_str_trim.c utils/spaces.c src/set_minimap.c src/move.c src/key_release.c src/rendring.c utils/error.c utils/close.c \
		src/cast_to_3d.c src/mouse_press.c src/key_press.c src/mouse_move.c src/render_game.c src/mouse_release.c src/map_animation.c src/design_env.c

FLGS	= gcc -Werror -Wall -Wextra

RM		= rm -f

all:	$(NAME) $(SRCS)

$(NAME): $(SRCS)
	make -C lib
	cd img/guns
	tar -xf g1.zip
	tar -xf g2.zip
	tar -xf g3.zip
	tar -xf g4.zip
	tar -xf g5.zip
	tar -xf g6.zip
	tar -xf g7.zip
	tar -xf g8.zip
	tar -xf g9.zip
	cd ../../
	$(FLGS)  -lmlx -framework OpenGL -framework AppKit -Ofast -g3 -flto -march=native  -O3 -ffast-math -msse4.2 -mtune=intel lib/libmlx.a $(SRCS) -o $(NAME)

clean: 
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: clean fclean all re