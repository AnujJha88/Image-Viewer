viewer:main.c
	gcc -Wall -Wextra -g -o viewer main.c `sdl2-config --cflags --libs`
