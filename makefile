CFLAGS=-Wall
LDFLAGS=-Wl,-rpath,/opt/homebrew/Cellar/sfml/2.6.1/lib

build: ./src/*.cpp
	g++ -std=c++17 -c -I/opt/homebrew/Cellar/sfml/2.6.1/include ./src/*.cpp -L/opt/homebrew/Cellar/sfml/2.6.1/lib
	mkdir -p obj && mv ./*.o ./obj
	g++ ./obj/*.o -I/opt/homebrew/Cellar/sfml/2.6.1/include -o main -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system 
	chmod 755 ./main
	./main
