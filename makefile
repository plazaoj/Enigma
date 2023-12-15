VER=`git describe --tags`
HPP=enigma.hpp ruedas.hpp maquina.hpp
OBJ=enigma.o ruedas.o main.o maquina.o
CFLAG=-Wall -fopenmp -O3 -DENIGMAVERSION=\"$(VER)\"

all: Enigma

Enigma:$(OBJ) $(HPP)
	g++ -o $@ $(OBJ) -lreadline

Enigma.o: ruedas.hpp enigma.hpp enigma.cpp
	g++ $(CFLAG) -c Enigma.cpp

Ruedas.o: ruedas.hpp ruedas.cpp
	g++ $(CFLAG) -c Ruedas.cpp

main.o: enigma.hpp ruedas.hpp main.cpp
	g++ $(CFLAG) -c main.cpp

maquina.o: enigma.hpp maquina.cpp maquina.hpp
	g++ $(CFLAG) -c maquina.cpp
clear:
	rm *.o
