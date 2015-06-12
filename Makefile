NAME = Newtonian_Fluid

all: debug release

debug:
	g++ -std=c++11 -D_DEBUG -L ./Libs/lib/ -I ./Libs/include/ -I ./Demo/Inc/ ./Demo/Src/*.cpp -lGLEW -lbass -lglfw -lGL -lm -lX11 -lXxf86vm -lpthread -lrocket -o demo_debug

release:
	g++ -std=c++11 -L ./Libs/lib/ -I ./Libs/include/ -I ./Demo/Inc/ ./Demo/Src/*.cpp -lGLEW -lbass -lglfw -lGL -lm -lX11 -lXxf86vm -lpthread -lrocket-player -o Newtonian_Fluid
