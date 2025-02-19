#include <iostream>
#include <set>

void simulateWork(int _size){
	std::set<int> temp;
	for(int i=0;i<_size;i++) temp.insert(i);
	while(temp.size()){
		int curent_choise=rand()%_size+0;
		if(temp.count(curent_choise)) temp.erase(curent_choise);
	}
}

int main(){
	std::cout<<"Start on size=16. ";
	simulateWork(16);
	std::cout<<"Complete.\n";

	std::cout<<"Start on size=32. ";
	simulateWork(32);
	std::cout<<"Complete.\n";

	std::cout<<"Start on size=64. ";
	simulateWork(64);
	std::cout<<"Complete.\n";

	std::cout<<"Start on size=128. ";
	simulateWork(128);
	std::cout<<"Complete.\n";

	return 0;
}