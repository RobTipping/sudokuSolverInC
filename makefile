gameTest: main.c
	gcc main.c -lraylib -lGL -lm -lpthread -lrt -DUSE_WAYLAND=ON -o ./build/gameTest
