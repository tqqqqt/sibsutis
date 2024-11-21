#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <fstream>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


#include "numbermath.h"
#include "lab1lib.h"

class client_info{
public:
	int socket;
	int turn;
	std::string v;
	std::string x;
	std::string y;
	int e;
	int count_turn;


	client_info(int _socket){
		socket=_socket;
		turn=0;
		v="";
		x="";
		y="";
		e=0;
		count_turn=0;
	}
};

void readPrims(std::vector<long long>& mas){
	std::ifstream file_in("prim2.txt");
	long long temp=0;
	while(file_in>>temp) mas.push_back(temp);
	file_in.close();
}

int main(){
	//create server
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

	//start protocol
	std::vector<long long> prim_mas;
	readPrims(prim_mas);
	//create p q
	long long p=prim_mas[prim_mas.size()-1-rand()%10], q=prim_mas[prim_mas.size()-1-rand()%10];
	//create n
	long long n=p*q;

	std::vector<client_info> clients;
	int new_client, c=sizeof(sockaddr_in);
	std::cout<<"p="<<p<<", q="<<q<<", n="<<n<<'\n';
	std::string mes="";
	char buffer[1024];
	std::ofstream file_keys("server_saves.txt");
	while(1){
		new_client=accept(socket_server,(sockaddr*)&client,(socklen_t*)&c);
		if(new_client!=-1){
			//add new client
			std::cout<<"New client = "<<new_client<<".\n";
			clients.push_back(client_info(new_client));
		}
		for(int i=0;i<clients.size();i++){
			if(clients[i].turn==0){ //send n to client
				mes=std::to_string(n);
				if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
					std::cout<<"Error send.";
					return -1;
				}
				clients[i].turn=1;
			}
			else if(clients[i].turn==1){ //get V client
				int temp=0;
				ioctl(clients[i].socket,SIOCINQ,&temp);
				if(temp<=0) continue;
				memset(buffer,0,1024);
				if(recv(clients[i].socket,buffer,1024,0)<0){
					std::cout<<"Error read.\n";
					return -1;
				}
				clients[i].v=buffer;
				mes="ok";
				if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
					std::cout<<"Error send.";
					return -1;
				}
				clients[i].turn=2;
				std::string ttemp=std::to_string(clients[i].socket)+" "+clients[i].v;
				file_keys<<ttemp<<'\n';
				file_keys.flush();
			}
			else if(clients[i].turn==2){ //get x client
				int temp=0;
				ioctl(clients[i].socket,SIOCINQ,&temp);
				if(temp<=0) continue;
				memset(buffer,0,1024);
				if(recv(clients[i].socket,buffer,1024,0)<0){
					std::cout<<"Error read.\n";
					return -1;
				}
				clients[i].x=buffer;
				mes="ok";
				if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
					std::cout<<"Error send.";
					return -1;
				}
				clients[i].turn=3;
			}
			else if(clients[i].turn==3){ // send e to client
				clients[i].e=1-clients[i].e;
				mes=std::to_string(clients[i].e);
				if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
					std::cout<<"Error send.";
					return -1;
				}
				clients[i].turn=4;
			}
			else if(clients[i].turn==4){ //get y client
				int temp=0;
				ioctl(clients[i].socket,SIOCINQ,&temp);
				if(temp<=0) continue;
				memset(buffer,0,1024);
				if(recv(clients[i].socket,buffer,1024,0)<0){
					std::cout<<"Error read.\n";
					return -1;
				}
				clients[i].y=buffer;
				mes="okk";
				if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
					std::cout<<"Error send.";
					return -1;
				}
				clients[i].turn=5;
			}
			else if(clients[i].turn==5){ //check result and send answer
				std::string temp_y=findModule(clients[i].y,2,std::to_string(n));
				std::string temp_right="";
				if(clients[i].e==1) temp_right=MathModDiv(MathMul(clients[i].x,findModule(clients[i].v,clients[i].e,std::to_string(n))),std::to_string(n));
				else if(clients[i].e==0) temp_right=MathModDiv(clients[i].x,std::to_string(n));
				if(temp_y==temp_right){
					if(++clients[i].count_turn>=20){
						std::cout<<"Client = ["<<clients[i].socket<<"] join in server.\n";
						mes="Welcome";
						if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
							std::cout<<"Error send.";
							return -1;
						}
						clients.erase(clients.begin()+i);
					}
					else{
						mes="ok";
						if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
							std::cout<<"Error send.";
							return -1;
						}
						clients[i].turn=2;
					}
				}
				else{
					std::cout<<"Client =["<<clients[i].socket<<"] died.\n";
					mes="Who are you?";
					if(send(clients[i].socket,mes.c_str(),sizeof(mes),0)<0){
						std::cout<<"Error send.";
						return -1;
					}
					clients.erase(clients.begin()+i);
				}
			}
		}
	}
	close(socket_server);
	file_keys.close();
	return 0;
}