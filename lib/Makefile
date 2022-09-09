#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

all: $(NOM)

$(NOM):	$(OBJ)
	tar -xf ../img/guns/g1.zip
	tar -xf ../img/guns/g2.zip
	tar -xf ../img/guns/g3.zip
	tar -xf ../img/guns/g4.zip
	tar -xf ../img/guns/g5.zip
	tar -xf ../img/guns/g6.zip
	tar -xf ../img/guns/g7.zip
	tar -xf ../img/guns/g8.zip
	tar -xf ../img/guns/g9.zip
	mv g* ../img/guns
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all
