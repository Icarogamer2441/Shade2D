CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./src
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

SRC_DIR = src
TEST_DIR = tests
INSTALL_PREFIX = /usr/local

all: libshade2d

libshade2d:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/shade2dlib.c -o $(SRC_DIR)/shade2dlib.o
	ar rcs libshade2d.a $(SRC_DIR)/shade2dlib.o

tests: libshade2d bouncing_ball moving_square clickable_button

bouncing_ball: libshade2d $(TEST_DIR)/bouncing_ball.c
	$(CC) $(CFLAGS) $(TEST_DIR)/bouncing_ball.c -L. -lshade2d $(LDFLAGS) -o $(TEST_DIR)/bouncing_ball

moving_square: libshade2d $(TEST_DIR)/moving_square.c
	$(CC) $(CFLAGS) $(TEST_DIR)/moving_square.c -L. -lshade2d $(LDFLAGS) -o $(TEST_DIR)/moving_square

clickable_button: libshade2d $(TEST_DIR)/clickable_button.c
	$(CC) $(CFLAGS) $(TEST_DIR)/clickable_button.c -L. -lshade2d $(LDFLAGS) -o $(TEST_DIR)/clickable_button

install: libshade2d
	mkdir -p $(INSTALL_PREFIX)/lib
	mkdir -p $(INSTALL_PREFIX)/include/shade2d
	cp libshade2d.a $(INSTALL_PREFIX)/lib/
	cp $(SRC_DIR)/shade2dlib.h $(INSTALL_PREFIX)/include/shade2d/
	ldconfig

uninstall:
	rm -f $(INSTALL_PREFIX)/lib/libshade2d.a
	rm -rf $(INSTALL_PREFIX)/include/shade2d

clean:
	rm -f $(SRC_DIR)/*.o libshade2d.a $(TEST_DIR)/bouncing_ball $(TEST_DIR)/moving_square $(TEST_DIR)/clickable_button

.PHONY: all clean libshade2d tests install uninstall bouncing_ball moving_square clickable_button
