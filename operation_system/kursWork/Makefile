SERVER = server
CLIENT = client

CLIENT_NAME = client
SERVER_NAME = server
CLIENT_LIB = libclient
SERVER_LIB = libserver

LIBCLI_NAME = libclient
LIBSER_NAME = libserver

DIR = dir
BIN = bin
OBJ = obj
SRC = src

SERVER_PATH = $(BIN)/$(SERVER)
CLIENT_PATH = $(BIN)/$(CLIENT)
LIBCLI_PATH = $(OBJ)/$(SRC)/$(LIBCLI_NAME).a
LIBSER_PATH = $(OBJ)/$(SRC)/$(LIBSER_NAME).a

SERVER_SRC = $(shell find $(SRC)/$(SERVER_NAME) -name '*.c')
SERVER_OBJ = $(SERVER_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

LIBSER_SRC = $(shell find $(SRC)/$(SERVER_LIB) -name '*.c')
LIBSER_OBJ = $(LIBSER_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

CLIENT_SRC = $(shell find $(SRC)/$(CLIENT_NAME) -name '*.c')
CLIENT_OBJ = $(CLIENT_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

LIBCLI_SRC = $(shell find $(SRC)/$(CLIENT_LIB) -name '*.c')
LIBCLI_OBJ = $(LIBCLI_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

DEPS = $(SERVER_OBJ:.o=.d) $(LIBSER_OBJ:.o=.d) $(CLIENT_OBJ:.o=.d) $(LIBCLI_OBJ:.o=.d)

.PHONY: $(CLIENT)
$(CLIENT): $(SERVER_PATH) $(CLIENT_PATH)

-include $(DEPS)

$(CLIENT_PATH): $(CLIENT_OBJ) $(LIBCLI_PATH)
	mkdir -p bin
	gcc $^ -I src -o $@

$(SERVER_PATH): $(SERVER_OBJ) $(LIBSER_PATH)
	mkdir -p bin
	gcc $^ -I src -o $@

$(LIBSER_PATH): $(LIBSER_OBJ)
	ar rcs $@ $^

$(LIBCLI_PATH): $(LIBCLI_OBJ)
	ar rcs $@ $^

$(OBJ)/%.o: %.c
	@mkdir -p $(@D)
	gcc -c $< -I src -o $@

.PHONY: clear
clear:
	rm -r -f bin
	rm -r -f obj
