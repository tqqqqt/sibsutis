main: server client

server: numbermath.cpp lab1lib.cpp prim2.txt server.cpp
	g++ numbermath.cpp lab1lib.cpp server.cpp -o server

client: numbermath.cpp lab1lib.cpp client.cpp
	g++ numbermath.cpp lab1lib.cpp client.cpp -o client

.PHONY: clear
clear:
	rm -f server
	rm -f client
	rm -f server_saves.txt