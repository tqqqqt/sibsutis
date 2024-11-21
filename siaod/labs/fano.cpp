#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <fstream>
#include <afxres.h>
#include <graphics.h>
#include <windows.h>

struct itemDataBase {
	char depositor[30];
	unsigned short int contribution;
	char date[10];
	char lawyer[22];
};
struct listDataBase {
	listDataBase *next;
	union {
		itemDataBase data;
		unsigned char Digit[sizeof(data)];
	};
};
struct coding {
	char symbol; // Символ
	unsigned int quantity; // Встречаемость в текте
	float probability; // Вероятность
	unsigned short int lengthCW; // Длина кодового слова
	char * codeword; // Кодовое слово
};
void readDataBase(listDataBase *&p, unsigned int & size) {
	std::fstream *file = new std::fstream;
	file->open("testBase3.dat", std::ios::in | std::ios::binary);
	itemDataBase* data = new itemDataBase;
	listDataBase* temp = p = new listDataBase;
	file->read((char *)data, sizeof(*data)).eof();
	temp->data = *data;
	size++;
	while (!file->read((char *)data, sizeof(*data)).eof()) {
		temp->next = new listDataBase;
		temp = temp->next;
		temp->data = *data;
		size++;
	}
	temp->next = NULL;
	file->close();
}
void quickSortCoding(coding* A, int R, int L) { // Сортировка для кодировки (сортировка по убыванию вероятности)
	while (L < R) {
		float x = A[L].probability;
		int i = L;
		int j = R;
		while (i <= j) {
			while (A[i].probability > x)
				i++;
			while (A[j].probability < x)
				j--;
			if (i <= j) {
				char tmp_ch;
				tmp_ch = A[i].symbol;
				A[i].symbol = A[j].symbol;
				A[j].symbol = tmp_ch;

				unsigned int tmp_q;
				tmp_q = A[i].quantity;
				A[i].quantity = A[j].quantity;
				A[j].quantity = tmp_q;

				float tmp_prop;
				tmp_prop = A[i].probability;
				A[i].probability = A[j].probability;
				A[j].probability = tmp_prop;
				i++;
				j--;
			}
		}
		if (j - L > R - i) {
			quickSortCoding(A, R, i);
			R = j;
		} else {
			quickSortCoding(A, j, L);
			L = i;
		}
	}
}
//Находит медиану части массива P, т.е. такой индекс L <= m <= R, что минимальна величина
int med(coding *code, int borderL, int borderR) {
	float SumL = 0;
	for (int i = borderL; i < borderR; i++)
		SumL = SumL + code[i].probability;
	float SumR = code[borderR].probability;
	int m = borderR;
	while (SumL >= SumR) {
		m = m - 1;
		SumL = SumL - code[m].probability;
		SumR = SumR + code[m].probability;
	}
	return m;
}
void codeFano(coding * code, int borderL, int borderR, int k) {
	//k - длина уже построенной части элементарных кодов
	if (borderL < borderR) {
		k = k + 1;
		int m = med(code, borderL, borderR);
		for (int i = borderL; i <= borderR; i++) {
			if (code[i].codeword) {
				char *temp = new char[k + 1];
				for(int j = 0; j < k - 1; j++)
					temp[j] = code[i].codeword[j];
				delete[] code[i].codeword;
				code[i].codeword = temp;
			} else
				code[i].codeword = new char[k + 1];
			if (i <= m)
				code[i].codeword[k - 1] = '0';
			else
				code[i].codeword[k - 1] = '1';
			code[i].codeword[k] = '\0';
			code[i].lengthCW = code[i].lengthCW+ 1;
		}
		codeFano(code, borderL, m, k);
		codeFano(code, m + 1, borderR, k);
	}
}
void tableSymbols(coding* &code, int &numsUnique) {
	int windows866[256] = {0};
	int totalNums = 0;
	char ch;
	std::fstream file("testBase3.dat", std::ios::in | std::ios::binary);
	while (!file.read((char*)&ch, sizeof(ch)).eof()) {
		totalNums++;
		if (int(ch) < 0)
			windows866[int(ch) + 256]++;
		else
			windows866[int(ch)]++;
	}
	file.close();
	for (int i = 0; i < 256; i++)
		if (windows866[i] != 0 )
			numsUnique++;
	code = new coding[numsUnique];
	unsigned short int temp = 0;
	for (int i = 0; i < 256; i++) {
		if(windows866[i] != 0) {
			code[temp].symbol = char(i);
			code[temp].quantity = windows866[i];
			code[temp].probability = (float)windows866[i] / (float)totalNums;
			temp++;
		}
	}
	quickSortCoding(code, numsUnique - 1, 0);
	codeFano(code, 0, numsUnique - 1, 0);
}
void printTableSymbols(coding *code, int numSymbols) {
	system("CLS");
	std::cout << " ===========T==================T==========================T==========================T================================ " << "\n";
	std::cout << "|" << std::setw(11) << "" << "|" << std::setw(18) << "" << "|" << std::setw(26) << "" << "|" << std::setw(26) << "" << "|" << std::setw(32) << "" << "|" << "\n";
	std::cout << "|" << "Code symbol" << "|" << " Number in text   " << "|" << "   quantity in text       " << "|" << "   length of code word    " << "|" << "          Code word             " << "|" << "\n";
	std::cout << "|" << std::setw(11) << "" << "|" << std::setw(18) << "" << "|" << std::setw(26) << "" << "|" << std::setw(26) << "" << "|" << std::setw(32) << "" << "|" << "\n";
	std::cout << "|===========+==================+==========================+==========================+================================|" << "\n";
	float entropy = 0;
	float averageLength = 0;
	for (int i = 0; i < numSymbols; i++) {
		entropy += code[i].probability * log2(code[i].probability);
		averageLength += (float)code[i].lengthCW * code[i].probability;
		std::cout << "|"
		          << std::setw(7) << (int)(unsigned char)code[i].symbol << std::setw(4) << "" << "|"
		          << std::setw(15) << code[i].quantity  << std::setw(3) << "" << "|"
		          << std::setw(23) << std::fixed << code[i].probability << std::setw(3) << "" << "|"
		          << std::setw(23) << code[i].lengthCW << std::setw(3) << "" << "|"
		          << std::setw(29) << code[i].codeword << std::setw(3) << "" << "|" << "\n";
	}
	std::cout << "L===========|==================|==========================|==========================|================================-" << "\n";
	std::cout << "  Entropy: " << -entropy << "\n";
	std::cout << "  Average length : " << averageLength << "\n";
}
int main(int argc, char const *argv[]) {
	listDataBase * listBase = NULL;
	unsigned int sizeBase = 0;
	readDataBase(listBase, sizeBase);
	int  numSymbols = 0;
	coding * codeFano = NULL;
	tableSymbols(codeFano, numSymbols);
	printTableSymbols(codeFano, numSymbols);
	return 0;
}
