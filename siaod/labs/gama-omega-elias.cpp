#include <iostream>
#include <iomanip>
#include <windows.h>
#include <math.h>
#include <stdint.h>

using namespace std;

string binary(uint8_t num){
	string answer = "";
	for(int i = sizeof(num) * 8; i > 0; i--) {
		if((num & (1 << (i - 1))) != 0) answer += '1';
		else answer += '0';
	}
	return answer;
}

string fixedVariable(uint8_t num){
	short int size = 8 * sizeof(num);
	uint8_t order = 0;
	string answer = "";
	for(int i = size; i > 0; i--) {
		if((num & ( 1 << (i - 1))) != 0) {
			order = i;
			break;
		}
	}
	int temp = 0;
	while(pow(2, temp) <= size) temp++;
	for(int i = temp; i > 0; i--) {
		if((order & (1 << (i - 1))) != 0) answer += '1';
		else answer += '0';
	}
	answer += ' ';
	for(int i = (order - 1); i > 0; i--) {
		if((num & (1 << (i - 1))) != 0) answer += '1';
		else answer += '0';
	}
	return answer;
}

string gammaCodeElias(uint8_t num){
	short int size = 8 * sizeof(num);
	uint8_t order = 0;
	string answer = "";
	for(int i = size; i > 0; i--) {
		if((num & ( 1 << ( i- 1))) != 0) {
			order = i;
			break;
		}
	}
	for(int i = (order - 1); i > 0; i--) answer += '0';
	answer += ' ';
	for(int i = order; i > 0; i--) {
		if((num & (1 << (i - 1))) != 0) answer += '1';
		else answer += '0';
	}
	return answer;
}

string omegaCodeElias(uint8_t num){
	if (num == 0) return "";
	short int size = 8 * sizeof(num);
	uint8_t order = 0;
	string temp = "";
	string answer = "0";
	while (num != 1) {
		temp = "";
		for(int i = size; i > 0; i--) {
			if((num & ( 1 << ( i- 1))) != 0) {
				order = i;
				break;
			}
		}
		for(int i = order; i > 0; i--) {
			if((num & (1 << (i - 1))) != 0) {
				temp += '1';
			} else temp += '0';
		}
		temp += " " + answer;
		answer = temp;
		num = order - 1;
	}
	return answer;
}

int main(int argc, const char **argv){
	uint8_t	number = 0;
	int vvod = 0;
	cout  <<"Number\t   "<< "|\tBinary code\t|" << "\t\tF+V|\tgamma-kod Ellias\t|\tomega-kod Ellias   |" << "\n";
	do {
		cout<<" Number -> ";
		cin>>vvod;
		if(vvod<0) break;
		while(number!=vvod) number+=1;
		cout << (int)number;
		cout << " |  "<<setw(24)<< binary(number) << " | "<< setw(24)<<fixedVariable(number) << " | "<< setw(24)<<gammaCodeElias(number) << " |"<< setw(24)<<omegaCodeElias(number) << "\n";
		number ++;
	} while(true);
	return 0;
}
