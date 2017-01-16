INC_DIR = includes
SRC_DIR = src
OBJ_DIR = build
CFLAGS  = -Wall -std=c++0x
INCLUDES = -Iincludes
SRCS = $(SRC_DIR)/mcd2klusta.cpp $(SRC_DIR)/mcd2mat.cpp
OBJS = $(OBJ_DIR)/mcd2klusta.o
# Note: The above will soon get unwieldy.
# The wildcard and patsubt commands will come to rescue.

MCD_LIB=MC_StreamAnsiLib/libMCStreamd.a


all: $(OBJS) $(OBJ_DIR)/mcd2klusta $(OBJ_DIR)/mcd2mat

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

(OBJ_DIR)/mcd2klusta.o:

$(OBJ_DIR)/mcd2klusta: $(OBJ_DIR)/mcd2klusta.o $(MCD_LIB)
	g++ -IMC_StreamAnsiLib -o $@ $^

$(OBJ_DIR)/mcd2mat: $(MCD_LIB) $(MATLAB_LIB)
	mex -v CFLAGS='$(CFLAGS)' $(INCLUDES) -lMCStreamd -LMC_StreamAnsiLib src/mcd2mat.cpp
	mv mcd2mat.mexa64 $(OBJ_DIR)/
	cp MC_StreamAnsiLib/libMCStreamd.so $(OBJ_DIR)/

clean:
	rm -rf $(OBJ_DIR)
