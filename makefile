gameTest: main.c
	gcc main.c solver.c -lraylib -lGL -lm -lpthread -lrt -DUSE_WAYLAND=ON -o ./build/gameTest.out
