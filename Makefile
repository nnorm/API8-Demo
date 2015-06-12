NAME = Newtonian_Fluid

SRC_CPP = ./Demo/Src/*.cpp
INC_H = ./Demo/Inc/*.h
INC_PATH = ./Demo/Inc/
LIB = ./Libs/lib/
INC_LIB = ./Libs/include/

LIBS = libbass.so librocket-player.a libGLEW.a libglfw.a

all: debug release

debug:
	g++ -std=c++11 -D_DEBUG -L ./Libs/lib/ -I ./Libs/include/ -I ./Demo/Inc/ ./Demo/Inc/  -llibbass.so -llibrocket-player.a -llibGLEW.a -llibglfw.a ./Demo/Src/*.cpp -o demo_debug

release:
	g++ -B $(LIB) $(INC_LIB) -o ./Bin/Release/$(NAME) $(SRC)
