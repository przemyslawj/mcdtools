INC_DIR = includes
SRC_DIR = src
OBJ_DIR = build
CFLAGS  = -Wall -std=c++0x
INCLUDES = -Iincludes
SRCS = $(SRC_DIR)/mcdio.cpp $(SRC_DIR)/mcd2klusta.cpp $(SRC_DIR)/mcd2mat.cpp $(SRC_DIR)/read_channel.cpp $(SRC_DIR)/mcd_fileinfo.cpp $(SRC_DIR)/findspikes.cpp $(SRC_DIR)/bwbpf.cpp $(SRC_DIR)/test_bwbpf.cpp

OBJS = $(OBJ_DIR)/mcd2klusta.o $(OBJ_DIR)/mcdio.o $(OBJ_DIR)/findspikes.o $(OBJ_DIR)/test_findspikes.o $(OBJ_DIR)/test_bwbpf.o

# Note: The above will soon get unwieldy.
# The wildcard and patsubt commands will come to rescue.

MCD_LIB=MC_StreamAnsiLib/libMCStreamd.a


all: $(OBJS) $(OBJ_DIR)/mcd2klusta $(OBJ_DIR)/mcd2mat $(OBJ_DIR)/mcd_fileinfo $(OBJ_DIR)/mcd2spikes

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

(OBJ_DIR)/mcd2klusta.o:

$(OBJ_DIR)/mcd2klusta: $(OBJ_DIR)/mcd2klusta.o $(MCD_LIB)
	g++ -IMC_StreamAnsiLib -o $@ $^

$(OBJ_DIR)/mcd2spikes: $(OBJ_DIR)/mcd2spikes.o $(OBJ_DIR)/mcdio.o $(OBJ_DIR)/findspikes.o $(OBJ_DIR)/bwbpf.o $(MCD_LIB)
	g++ -IMC_StreamAnsiLib -o $@ $^

$(OBJ_DIR)/mcd2mat: $(MCD_LIB) $(MATLAB_LIB)
	mex -v CFLAGS='$(CFLAGS)' $(INCLUDES) -lMCStreamd -LMC_StreamAnsiLib -outdir $(OBJ_DIR) src/mcd2mat.cpp
	cp MC_StreamAnsiLib/libMCStreamd.so $(OBJ_DIR)/

$(OBJ_DIR)/read_channel: $(MCD_LIB) $(MATLAB_LIB)
	mex -v CFLAGS='$(CFLAGS)' $(INCLUDES) -lMCStreamd -LMC_StreamAnsiLib -outdir $(OBJ_DIR) src/read_channel.cpp
	cp MC_StreamAnsiLib/libMCStreamd.so $(OBJ_DIR)/

$(OBJ_DIR)/mcd_fileinfo: $(MCD_LIB) $(MATLAB_LIB)
	mex -v CFLAGS='$(CFLAGS)' $(INCLUDES) -lMCStreamd -LMC_StreamAnsiLib -outdir $(OBJ_DIR) src/mcd_fileinfo.cpp
	cp MC_StreamAnsiLib/libMCStreamd.so $(OBJ_DIR)/

$(OBJ_DIR)/test_findspikes: $(OBJ_DIR)/test_findspikes.o $(OBJ_DIR)/findspikes.o
	g++ -o $@ $^

$(OBJ_DIR)/test_bwbpf: $(OBJ_DIR)/bwbpf.o $(OBJ_DIR)/test_bwbpf.o
	g++ -o $@ $^

clean:
	rm -rf $(OBJ_DIR)

test: $(OBJ_DIR)/test_findspikes
	./$(OBJ_DIR)/test_findspikes

