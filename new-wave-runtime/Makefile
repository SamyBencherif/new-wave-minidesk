linux:
	gcc -o nw -Iraylib/src source.c -lraylib -flto -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lXmu -lGLdispatch -lXau -lXdmcp

osx:
	gcc -o nw -Iraylib/src source.c -lraylib -flto -lm -ldl -lpthread -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
