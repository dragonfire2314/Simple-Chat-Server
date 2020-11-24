client:
	g++ -c library.cpp
	ar rvs library.a library.o
	g++ -std=c++11 client.cpp library.a -pthread -o client.out

server:
	g++ -c library.cpp
	ar rvs library.a library.o
	g++ -std=c++11 server.cpp library.a -pthread -o server.out