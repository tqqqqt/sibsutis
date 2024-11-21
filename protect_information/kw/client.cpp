#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){
	int socket_client, temp_length=0;
	sockaddr_in server_addr, client_addr;
	hostent *hp;
	if(argc<2){
		std::cout<<"Error arguments.\n";
		return -1;
	}
	if((socket_client=socket(AF_INET,SOCK_STREAM,0))<0){
		std::cout<<"Error client socket.\n";
		return -1;
	}
	server_addr.sin_family=AF_INET;
	hp=gethostbyname("localhost");
	bcopy(hp->h_addr,&server_addr.sin_addr,hp->h_length);
	server_addr.sin_port=htons(atoi(argv[2]));
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	client_addr.sin_port=0;
	if(bind(socket_client,(sockaddr*)&client_addr,sizeof(client_addr))){
		std::cout<<"Error bind.\n";
		return -1;
	}
	char buffer[1024];
	int length=sizeof(server_addr);
	connect(socket_client,(sockaddr*)&server_addr,sizeof(server_addr));
	close(socket_client);
	return 0;
}