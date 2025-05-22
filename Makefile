start: main.o funkcijos.o
	g++ main.o funkcijos.o -o main -O3
	rm -f main.o funkcijos.o

main.o: main.cpp funkcijos.h
	g++ -O3 -c main.cpp -o main.o

funkcijos.o: funkcijos.cpp funkcijos.h
	g++ -O3 -c funkcijos.cpp -o funkcijos.o
