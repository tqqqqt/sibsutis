#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <tuple>
#include <utility>

#include "lab1lib.h"

long long randomPrim(std::string file_name){
	srand(time(nullptr));
	std::ifstream file(file_name);
	std::vector<long long> mas;
	long long temp=0;
	while(file>>temp) mas.push_back(temp);
	temp=rand()%15+1;
	return mas[mas.size()-temp];
}

void shuffleCards(std::vector<std::string>& coloda){
	int len=coloda.size(), temp=0;
	for(int i=0;i<len;i++){
		temp=rand()%(len-1)+0;
		std::swap(coloda[i],coloda[temp]);
	}
}

int main(int argc, char* argv[]){
	/* check prop */
	if(argc!=3){
		std::cout<<"Error: args\n";
		return -1;
	}
	int count_players=std::stoi(argv[1]), count_cards=std::stoi(argv[2]);
	if(count_players<2){
		std::cout<<"Error: players<2\n";
		return -1;
	}
	if(count_cards-(count_players*2)<5){
		std::cout<<"Error: to many players\n";
		return -1;
	}
	if(count_cards>52){
		std::cout<<"Error: cards > 52\n";
		return -1;
	}
	std::vector<std::string> game_cards;
	for(int i=0, temp=13;i<count_cards;temp--){
		for(int j=0;i<count_cards && j<4;j++, i++){
			if(j==0) game_cards.push_back("S"+std::to_string(temp));
			else if(j==1) game_cards.push_back("C"+std::to_string(temp));
			else if(j==2) game_cards.push_back("D"+std::to_string(temp));
			else game_cards.push_back("H"+std::to_string(temp));
		}
	}
	std::cout<<"Info:\nNames masti:\n Diamonds=Bubni\n Hearts=Chervi\n Spades=Piki\n Clubs=Trefi\n";
	std::cout<<"Card nums:\n 13-tus, 12-korol, 11-dama, 10-valet, 9-10, 8-9 ... 1-2\n \n";
	std::cout<<"Full deck:\n";
	for(const std::string& x:game_cards) std::cout<<x<<", ";
	std::cout<<"\n \n";

	/* keys create */
	long long p=randomPrim("prim2.txt");
	std::unordered_map<int,std::vector<std::string>> players_keys;
	for(int i=-1;i<count_players;i++){
		std::string c="", d="";
		while(1){
			long long temp_c=rand()%(p-1)+1;
			if(std::get<0>(findNod(std::to_string(temp_c),std::to_string(p-1)))=="1"){
				c=std::to_string(temp_c);
				break;
			}
		}
		std::tuple<std::string,std::string,std::string> temp=findNod(c,std::to_string(p-1));
		std::string xx=std::get<1>(temp), yy=std::get<2>(temp);
		if(xx[0]=='-') xx=MathNeg(std::to_string(p-1),xx.substr(1));
		else xx=MathModDiv(xx,std::to_string(p-1));
		if(yy[0]=='-') yy=MathNeg(std::to_string(p-1),yy.substr(1));
		else yy=MathModDiv(yy,std::to_string(p-1));
		d=xx;
		players_keys[i]={c,d};
	}

	/* create coloda */
	std::unordered_map<int,std::string> keys_to_cards;
	std::vector<int> enc_cards;
	for(int i=0;i<game_cards.size();){
		long long temp_num=rand()%(p-1)+1;
		if(keys_to_cards.find(temp_num)!=keys_to_cards.end()) continue;
		keys_to_cards[temp_num]=game_cards[i];
		enc_cards.push_back(temp_num);
		i++;
	}

	/* drop cards to players and desk */
	std::vector<std::pair<std::string,std::string>> players_colods;
	std::unordered_map<std::string,int> u_to_enc;
	std::unordered_map<int,std::string> enc_to_u;
	std::vector<std::string> u;
	for(const int& x:enc_cards){
		u.push_back(findModule(std::to_string(x),stoll(players_keys[-1][0]),std::to_string(p)));
		u_to_enc[u.back()]=x;
		enc_to_u[x]=u.back();
	}
	for(int i=0;i<count_players;i++){
		shuffleCards(u);
		std::vector<std::string> uu=u;
		/*int bob_choise_1=rand()%(uu.size()-1)+0;
		uu.erase(uu.begin()+bob_choise_1);
		int bob_choise_2=rand()%(uu.size()-1)+0;
		uu.erase(uu.begin()+bob_choise_2);*/
		std::vector<std::string> v;
		for(const std::string& x:uu) v.push_back(findModule(x,stoll(players_keys[i][0]),std::to_string(p)));
		shuffleCards(v);
		int diler_choise=rand()%(v.size()-1)+0;
		std::string w_card_1=findModule(v[diler_choise],stoll(players_keys[-1][1]),std::to_string(p));
		v.erase(v.begin()+diler_choise);
		diler_choise=rand()%(v.size()-1)+0;
		std::string w_card_2=findModule(v[diler_choise],stoll(players_keys[-1][1]),std::to_string(p));
		v.erase(v.begin()+diler_choise);
		std::string z_card_1=findModule(w_card_1,stoll(players_keys[i][1]),std::to_string(p));
		std::string z_card_2=findModule(w_card_2,stoll(players_keys[i][1]),std::to_string(p));
		players_colods.push_back(make_pair(z_card_1,z_card_2));
		auto p1=find(u.begin(),u.end(),enc_to_u[std::stoi(z_card_1)]);
		u.erase(p1);
		auto p2=find(u.begin(),u.end(),enc_to_u[std::stoi(z_card_2)]);
		u.erase(p2);
	}
	std::vector<int> desk_cards;
	shuffleCards(u);
	for(int i=0;i<5;i++){
		if(u.size()==0) break;
		int ttemp=0;
		if(u.size()>1) ttemp=rand()%(u.size()-1)+0;
		else ttemp=0;
		desk_cards.push_back(u_to_enc[u[ttemp]]);
		u.erase(u.begin()+ttemp);
	}


	/* show result */
	std::cout<<"Players cards:\n";
	for(int i=0;i<players_colods.size();i++){
		std::cout<<i<<". => "<<keys_to_cards[std::stoi(players_colods[i].first)]<<", "<<keys_to_cards[std::stoi(players_colods[i].second)]<<'\n';
	}
	std::cout<<"\nTable cards:\n";
	for(int i=0;i<desk_cards.size();i++){
		std::cout<<keys_to_cards[desk_cards[i]]<<" ";
	}
	std::cout<<"\n";

	return 0;
}