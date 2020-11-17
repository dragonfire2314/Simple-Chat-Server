client:
	g++ -std=c++11 client.cpp library.cpp -pthread -o client.out
	./client.out

server:
	g++ -std=c++11 server.cpp library.cpp -pthread -o server.out
	./server.out