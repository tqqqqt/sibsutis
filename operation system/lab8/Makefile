lab: noT oneT threeT oneTcpp threeTcpp

noT: mainNoT.c
	gcc -o noT mainNoT.c -lm

oneT: mainOneT.c
	gcc -o oneT mainOneT.c -lpthread -lm

threeT: mainThreeT.c
	gcc -o threeT mainThreeT.c -lpthread -lm

oneTcpp: mainOneT.cpp
	g++ -o oneTcpp mainOneT.cpp -pthread 

threeTcpp: mainThreeT.cpp
	g++ -o threeTcpp mainThreeT.cpp -pthread

clear:
	rm noT oneT threeT oneTcpp threeTcpp
