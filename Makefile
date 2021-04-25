PATH_SRC=./src
PATH_BIN=./bin
PATH_OBJ=./obj
PATH_INC=./inc
PATH_DOC=./doc

CC=gcc
CFLAGS=-W -Wall -Wextra -I$(PATH_INC) `sdl-config --cflags` -g
LDFLAGS=`sdl-config --libs` -lSDL_image -lSDL_ttf

EXEC=$(PATH_BIN)/main

SRCS = $(wildcard $(PATH_SRC)/*.c)
OBJS = $(patsubst $(PATH_SRC)/%.c, $(PATH_OBJ)/%.o, $(SRCS))

.PHONY: all clean dist-clean doxy 

all: dir $(EXEC)  
	echo "All is ok !"
doxy:	
	@mkdir -p $(PATH_DOC)
	@doxygen

dir:
	@mkdir -p $(PATH_BIN)
	@mkdir -p $(PATH_OBJ)

$(EXEC):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	$(CC) -o $@ $^ -c $(CFLAGS)

clean:
	@rm -rf $(PATH_OBJ)

dist-clean: clean
	@rm -fr $(PATH_BIN)
	@rm -fr Documentation
	@rm -fr $(PATH_LIB)
