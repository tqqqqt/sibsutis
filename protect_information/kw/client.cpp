#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <utility>
#include <ctime>

#include "numbermath.h"
#include "lab1lib.h"

int main(int argc, char** argv){
	//create client
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
	server_addr.sin_port=htons(atoi(argv[1]));
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	client_addr.sin_port=0;
	if(bind(socket_client,(sockaddr*)&client_addr,sizeof(client_addr))){
		std::cout<<"Error bind.\n";
		return -1;
	}

	//connect
	char buffer[1024];
	memset(buffer,0,1024);
	int length=sizeof(server_addr);
	connect(socket_client,(sockaddr*)&server_addr,sizeof(server_addr));

	//get n
	if(recv(socket_client,buffer,1024,0)<0){
		std::cout<<"Error read.\n";
		close(socket_client);
		return -1;
	}
	std::string server_n=buffer;
	std::cout<<"Server n ="<<server_n<<'\n';

	//create s
	srand(time(nullptr));
	std::string s="";
	for(long long i=rand()%100+2;i<std::stoll(server_n)-1;i++){
		if(std::get<0>(findNod(std::to_string(i),server_n))=="1"){
			s=std::to_string(i);
			break;
		}
	}

	//create v
	std::string v=findModule(s,2,server_n);
	std::string mes=v;
	if(send(socket_client,mes.c_str(),sizeof(mes),0)<0){
		std::cout<<"Error send.";
		return -1;
	}
	if(recv(socket_client,buffer,1024,0)<0){
		std::cout<<"Error read.\n";
		close(socket_client);
		return -1;
	}

	while(1){
		//random r
		long long r=rand()%(std::stoll(server_n)-2)+1;
		//create x
		std::string x=findModule(std::to_string(r),2,server_n);
		mes=x;
		if(send(socket_client,mes.c_str(),sizeof(mes),0)<0){
			std::cout<<"Error send.";
			return -1;
		}
		if(recv(socket_client,buffer,1024,0)<0){
			std::cout<<"Error read.\n";
			close(socket_client);
			return -1;
		}
		//get e
		memset(buffer,0,1024);
		if(recv(socket_client,buffer,1024,0)<0){
			std::cout<<"Error read.\n";
			close(socket_client);
			return -1;
		}
		std::string e=buffer;
		//create y
		std::string y="";
		if(e=="0") y=std::to_string(r);
		else y=MathModDiv(MathMul(std::to_string(r),s),server_n);
		mes=y;
		if(send(socket_client,mes.c_str(),sizeof(mes),0)<0){
			std::cout<<"Error send.";
			return -1;
		}
		if(recv(socket_client,buffer,1024,0)<0){
			std::cout<<"Error read.\n";
			close(socket_client);
			return -1;
		}
		//get server answer
		//std::cout<<"r=["<<r<<"] x=["<<x<<"] e=["<<e<<"] y=["<<y<<"]\n";
		if(recv(socket_client,buffer,1024,0)<0){
			std::cout<<"Error read.\n";
			close(socket_client);
			return -1;
		}
		mes=buffer;
		if(mes=="ok"){
			std::cout<<"Check accept.\n";
			continue;
		}
		if(mes=="Welcome"){
			std::cout<<"I am in server.\n";
			break;
		}
		if(mes=="Who are you?"){
			std::cout<<"I am die.\n";
			break;
		}

	}

	//end work
	close(socket_client);
	return 0;
}