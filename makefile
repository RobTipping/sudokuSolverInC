CC = gcc
CFLAGS = -lraylib -lGL -lm -lpthread -lrt -DUSE_WAYLAND=ON -I$(IDIR)
IDIR = ./include
SRCDIR = ./src
BDIR = ./build
SoDuKuSolver: $(SRCDIR)/*.c
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(BDIR)/*
