all:
	g++ -Wall -g -I/usr/include/python3.7m -c main.cpp -o main.o
	g++ -o WSServer.out main.o -lpthread -lpython3.7m
	@-rm main.o
