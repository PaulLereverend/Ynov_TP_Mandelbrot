main.exe : main.o SDLProgram.o SDLException.o Mandelbrot.o
	g++ -o main.exe main.o SDLProgram.o SDLException.o Mandelbrot.o -lSDL2

main.o : main.cpp
	g++ -std=c++11 -c main.cpp -o main.o 
#Paramètre pour macos

SDLProgram.o : SDLProgram.cpp
	g++ -c SDLProgram.cpp  -o SDLProgram.o

SDLException.o : SDLException.cpp
	g++ -c SDLException.cpp -o SDLException.o

Mandelbrot.o : Mandelbrot.cpp
	g++ -c Mandelbrot.cpp -o Mandelbrot.o

clean : 
	rm *.o *.exe