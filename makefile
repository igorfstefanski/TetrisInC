all: tetris

tetris: tetris.o tetris_pieces.o tetris_fun.o primlib.o
	gcc -fsanitize=undefined -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.c primlib.h

tetris.o: tetris.c tetris_declarations.h primlib.h

tetris_pieces.o: tetris_pieces.c tetris_declarations.h primlib.h

tetris_fun.o: tetris_fun.c tetris_declarations.h primlib.h

clean:
	-rm primlib.o tetris.o tetris_pieces.o tetris_fun.o tetris
