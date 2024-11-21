all: noWrite turn posix peterson region

noWrite: mainNoWrite.c
	gcc -o noWrite mainNoWrite.c -lpthread

turn: mainTurn.c
	gcc -o turn mainTurn.c -lpthread

posix: mainPosix.c
	gcc -o posix mainPosix.c -lpthread

peterson: mainPeterson.c
	gcc -o peterson mainPeterson.c -lpthread

region: mainRegion.c
	gcc -o region mainRegion.c -lpthread

clear:
	rm noWrite turn posix peterson region
