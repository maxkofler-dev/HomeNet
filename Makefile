all:
	make clean
	g++ -Wall -g -c ./ConfigParser.cpp -o obj/Debug/ConfigParser.o
	g++ -Wall -g -c ./DriverListParser.cpp -o obj/Debug/DriverListParser.o
	g++ -Wall -g -c ./ExceptionClass.cpp -o obj/Debug/ExceptionClass.o
	g++ -Wall -g -I/usr/include/python3.8  -c ./HNPython.cpp -o obj/Debug/HNPython.o
	g++ -Wall -g -I/usr/include/python3.8  -c ./main.cpp -o obj/Debug/main.o
	g++ -Wall -g -c ./StartupMsg.cpp -o obj/Debug/StartupMsg.o
	g++ -Wall -g -I/usr/include/python3.8  -c ./Weathersens.cpp -o obj/Debug/Weathersens.o
	g++ -Wall -g -I/usr/include/python3.8  -c ./WSValueserver.cpp -o obj/Debug/WSValueserver.o
	g++ -Wall -g -I/usr/include/python3.8  -c ./HNNetworking.cpp -o obj/Debug/HNNetworking.o
	g++  -o ./WSServer.out obj/Debug/ConfigParser.o obj/Debug/DriverListParser.o obj/Debug/ExceptionClass.o obj/Debug/HNPython.o obj/Debug/main.o obj/Debug/StartupMsg.o obj/Debug/Weathersens.o obj/Debug/WSValueserver.o obj/Debug/HNNetworking.o -lpython3.7m -lpthread
	

clean:
	-rm -r obj
	mkdir obj
	mkdir obj/Debug

