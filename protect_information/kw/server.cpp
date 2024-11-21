#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int socket_server;
	sockaddr_in server, client;
	if((socket_server=socket(AF_INET,SOCK_STREAM,0))<0){
		std::cout<<"Error server create.\n";
		return -1;
	}
	int flags=fcntl(socket_server,F_GETFL);
	fcntl(socket_server,F_SETFL,flags|O_NONBLOCK);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=0;
	if(bind(socket_server,(sockaddr*)&server,sizeof(server))){
		std::cout<<"Error bind.\n";
		return -1;
	}
	int temp=sizeof(server);
	if(getsockname(socket_server,(sockaddr*)&server,(socklen_t*)&temp)){
		std::cout<<"Error getsockname.\n";
		return -1;
	}
	std::cout<<"Port="<<htons(server.sin_port)<<'\n';
	listen(socket_server,3);
	int new_client, c=sizeof(sockaddr_in);
	while(1){
		new_client=accept(socket_server,(sockaddr*)&client,(socklen_t*)&c);
		if(new_client==-1){
			std::cout<<"no cli.\n";
			sleep(1);
			//break;
		}
		else{
			std::cout<<"cli.\n";
			break;
		}
	}
	close(socket_server);
	return 0;
}