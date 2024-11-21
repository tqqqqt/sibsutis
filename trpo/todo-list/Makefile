APP = Todo
AP = list
LIB = lib
TEST = test

CFLAGS = -Wall -Werror
CPPFLAGS = -I src -MMD
TFLAG = -I src -I thirdparty -MMD

BIN = bin
SRC = src
OBJ = obj

APP_PATH = $(BIN)/$(APP)
LIB_PATH = $(OBJ)/$(SRC)/$(LIB)/$(LIB).a
TEST_PATH = $(BIN)/$(TEST)

APP_SRC = $(shell find $(SRC)/$(AP) -name '*.c')
APP_OBJ = $(APP_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

LIB_SRC = $(shell find $(SRC)/$(LIB) -name '*.c')
LIB_OBJ = $(LIB_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

TEST_SRC = $(shell find $(TEST) -name '*.c')
TEST_OBJ = $(TEST_SRC:$(TEST)/%.c=$(OBJ)/$(TEST)/%.o)

DEPS = $(APP_OBJ:.o=.d) $(LIB_OBJ:.o=.d) $(TEST_OBJ:.o=.d)

.PHONY: $(APP)
$(APP): $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJ) $(LIB_PATH)
	gcc $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_PATH): $(LIB_OBJ)
	ar rcs $@ $^

$(OBJ)/%.o: %.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: $(TEST)
$(TEST): $(TEST_PATH)

$(TEST_PATH): $(TEST_OBJ) $(LIB_PATH)
	gcc $(CFLAGS) $(TFLAG) $^ -o $@

$(OBJ)/%.o: %.c
	gcc -c $(CFLAGS) $(TFLAG) $< -o $@

.PHONY: clean
clean:
	rm -f $(APP_PATH)
	rm -f $(LIB_PATH)
	rm -f $(TEST_PATH)
	find $(OBJ) -name '*.o' -exec rm '{}' \;
	find $(OBJ) -name '*.d' -exec rm '{}' \;
