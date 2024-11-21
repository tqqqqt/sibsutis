SERVER = server

SERVER_NAME = mainserver
SERVER_LIB = libserver

LIBSER_NAME = libserver

DIR = dir
BIN = bin
OBJ = obj
SRC = src

SERVER_PATH = $(BIN)/$(SERVER)
LIBSER_PATH = $(OBJ)/$(SRC)/$(LIBSER_NAME).a


SERVER_SRC = $(shell find $(SRC)/$(SERVER_NAME) -name '*.c')
SERVER_OBJ = $(SERVER_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

LIBSER_SRC = $(shell find $(SRC)/$(SERVER_LIB) -name '*.c')
LIBSER_OBJ = $(LIBSER_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

DEPS = $(SERVER_OBJ:.o=.d) $(LIBSER_OBJ:.o=.d)

.PHONY: $(SERVER)
$(SERVER): $(SERVER_PATH)

-include $(DEPS)

$(SERVER_PATH): $(SERVER_OBJ) $(LIBSER_PATH)
	mkdir -p bin
	gcc $^ -I src -o $@

$(LIBSER_PATH): $(LIBSER_OBJ)
	ar rcs $@ $^

$(OBJ)/%.o: %.c
	@mkdir -p $(@D)
	gcc -c $< -I src -o $@

.PHONY: clear
clear:
	rm -r -f bin
	rm -r -f obj
