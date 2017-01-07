INC_DIR = includes
SRC_DIR = src
OBJ_DIR = build
CFLAGS  = -c -Wall -std=c++0x -IMC_StreamAnsiLib
SRCS = $(SRC_DIR)/mcd2klusta.cpp $(SRC_DIR)/mcd2klusta_test.cpp
OBJS = $(OBJ_DIR)/mcd2klusta.o
# Note: The above will soon get unwieldy.
# The wildcard and patsubt commands will come to rescue.

LIB=MC_StreamAnsiLib/libMCStreamd.a


all: $(OBJS) $(OBJ_DIR)/mcd2klusta

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

(OBJ_DIR)/mcd2klusta.o:

$(OBJ_DIR)/mcd2klusta: $(OBJ_DIR)/mcd2klusta.o $(LIB)
	g++ -IMC_StreamAnsiLib -o $@ $^

clean:
	rm -rf $(OBJ_DIR)
