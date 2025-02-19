APP = compLab

APP_NAME = comp
LIB_NAME = libcomp

AP1 = compLab1
AP2 = compLab2
AP3 = compLab3
AP4 = compLab4
AP5 = compLab5
AP6 = sat
AP7 = sbt

CFLAG = -Wall -Werror
CPPFLAG = -I src -MP -MMD
LIB = -l comp
LIB1 = -l mySimpleComputer
LIB2 = -l myTerm
LIB3 = -l myBigChars
LIB4 = -l myReadKey
LIB5 = -l CU
LIB6 = -l ALU
DLIB1 = -l ConsoleChars
DLIB2 = -l ConsoleContent

BIN = bin
OBJ = obj
SRC = src

APP_PATH = $(BIN)/$(APP)
LIB_PATH = $(OBJ)/$(SRC)/$(LIB_NAME)/$(LIB_NAME).a

APP_PPATH = $(OBJ)/$(SRC)/$(APP_NAME)
LIB_PPATH = $(OBJ)/$(SRC)/$(LIB_NAME)

AP1_PATH = $(BIN)/$(AP1)
AP2_PATH = $(BIN)/$(AP2)
AP3_PATH = $(BIN)/$(AP3)
AP4_PATH = $(BIN)/$(AP4)
AP5_PATH = $(BIN)/$(AP5)
AP6_PATH = $(BIN)/$(AP6)
AP7_PATH = $(BIN)/$(AP7)

APP_SRC = $(shell find $(SRC)/$(APP_NAME) -name '*.c')
APP_OBJ = $(APP_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)

LIB_SRC = $(shell find $(SRC)/$(LIB_NAME) -name '*.c')
LIB_OBJ = $(LIB_SRC:$(SRC)/%.c=$(OBJ)/$(SRC)/%.o)
LIB_LOBJ = $(LIB_SRC:$(SRC)/$(LIB_NAME)/%.c=$(OBJ)/$(SRC)/$(LIB_NAME)/lib%.a)

DEPS = $(APP_OBJ:.o=.d) $(LIB_OBJ:.o=.d)

.PHONY: $(APP)
$(APP): $(BIN) $(LIB_LOBJ) $(LIB_OBJ) $(APP_OBJ) $(AP1_PATH) $(AP2_PATH) $(AP3_PATH) $(AP4_PATH) $(AP5_PATH) $(AP6_PATH) $(AP7_PATH) $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(OBJ)/$(SRC)/$(LIB_NAME)/libmySimpleComputer.a $(OBJ)/$(SRC)/$(LIB_NAME)/libmyTerm.a $(OBJ)/$(SRC)/$(LIB_NAME)/libmyBigChars.a $(OBJ)/$(SRC)/$(LIB_NAME)/libConsoleChars.a $(OBJ)/$(SRC)/$(LIB_NAME)/libmyReadKey.a $(OBJ)/$(SRC)/$(LIB_NAME)/libCU.a $(OBJ)/$(SRC)/$(LIB_NAME)/libALU.a $(APP_PPATH)/new_main.o
	gcc $(CFLAG) $(CPPFLAG) -L$(LIB_PPATH) $(APP_PPATH)/new_main.o $(DLIB2) $(LIB1) $(LIB2) $(LIB3) $(LIB4) $(LIB5) $(LIB6) $(DLIB1) -o $@

$(AP1_PATH): $(OBJ)/$(SRC)/$(LIB_NAME)/libmySimpleComputer.a $(APP_PPATH)/main_lab1.o
	gcc $(CFLAG) $(CPPFLAG) -L$(LIB_PPATH) $(APP_PPATH)/main_lab1.o $(LIB1) -o $@

$(AP2_PATH): $(OBJ)/$(SRC)/$(LIB_NAME)/libmyTerm.a $(APP_PPATH)/main_lab2.o
	gcc $(CFLAG) $(CPPFLAG) -L$(LIB_PPATH) $(APP_PPATH)/main_lab2.o $(LIB2) -o $@

$(AP3_PATH): $(OBJ)/$(SRC)/$(LIB_NAME)/libmyTerm.a $(OBJ)/$(SRC)/$(LIB_NAME)/libmyBigChars.a $(OBJ)/$(SRC)/$(LIB_NAME)/libConsoleChars.a $(APP_PPATH)/main_lab3.o
	gcc $(CFLAG) $(CPPFLAG) -L$(LIB_PPATH) $(APP_PPATH)/main_lab3.o $(LIB3) $(LIB2) $(DLIB1) -o $@

$(AP4_PATH): $(OBJ)/$(SRC)/$(LIB_NAME)/libmyReadKey.a $(APP_PPATH)/main_lab4.o
	gcc $(CFLAG) $(CPPFLAG) -L$(LIB_PPATH) $(APP_PPATH)/main_lab4.o $(LIB4) -o $@

$(AP5_PATH): $(APP_PPATH)/main_lab5.o
	gcc $(CFLAG) $(CPPFLAG) $(APP_PPATH)/main_lab5.o -o $@

$(AP6_PATH): asemblerMain.cpp
	g++ asemblerMain.cpp -o $@

$(AP7_PATH): basicMain.cpp
	g++ basicMain.cpp -o $@

$(BIN):
	mkdir -p $(BIN)
	mkdir -p $(APP_PPATH)
	mkdir -p $(LIB_PPATH)

$(OBJ)/$(SRC)/$(LIB_NAME)/lib%.a: $(OBJ)/$(SRC)/$(LIB_NAME)/%.o
	ar rcs $@ $^

$(OBJ)/%.o: %.c
	gcc -c $(CFLAG) $(CPPFLAG) $< -o $@

.PHONY: format
format:
	find . -type f -name '*.[ch]' | xargs clang-format --style GNU -i --verbose

.PHONY: clean
clean:
	rm -f *.o *.d *.a *.txt
	rm -f $(APP) compLab1 compLab2 compLab3
	rm -rf $(OBJ) $(BIN)
