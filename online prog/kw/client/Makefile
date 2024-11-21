CLIENT = client

CLIENT_NAME = mainclient
CLIENT_LIB = libclient

LIBCLI_NAME = libclient

DIR = dir
BIN = bin
OBJ = obj
SRC = src

CLIENT_PATH = $(BIN)/$(CLIENT)
LIBCLI_PATH = $(OBJ)/$(SRC)/$(LIBCLI_NAME).a

CLIENT_SRC = $(shell find $(SRC)/$(CLIENT_NAME) -name '*.c')
CLIENT_OBJ = $(CLIENT_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

LIBCLI_SRC = $(shell find $(SRC)/$(CLIENT_LIB) -name '*.c')
LIBCLI_OBJ = $(LIBCLI_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

DEPS = $(CLIENT_OBJ:.o=.d) $(LIBCLI_OBJ:.o=.d)

.PHONY: $(CLIENT)
$(CLIENT): $(CLIENT_PATH)

-include $(DEPS)

$(CLIENT_PATH): $(CLIENT_OBJ) $(LIBCLI_PATH)
	mkdir -p bin
	gcc $^ -I src -o $@

$(LIBCLI_PATH): $(LIBCLI_OBJ)
	ar rcs $@ $^

$(OBJ)/%.o: %.c
	@mkdir -p $(@D)
	gcc -c $< -I src -o $@


.PHONY: clear
clear:
	rm -r -f bin
	rm -r -f obj
