all: main.cpp
	g++ -Wall -std=c++11 -o run main.cpp -lsqlite3

run: all
	./run

clean:
	rm -rf run