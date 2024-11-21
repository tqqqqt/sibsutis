#include <iostream>
#include <stdlib.h>
#include <time.h>

int* genRandArray(int size, int MaxValue){
	int *mas=new int[size+1];
	mas[0]=size;
	for(int i=1;i<=size;i+=1) mas[i]=1+rand()%50;
	return mas;
}

void print(int *arr, int size){
	std::cout<<arr[0]<<": ";
	for(int i=0;i<size;i+=1) std::cout<<arr[i]<<" ";
}

int** genRandMatrix(int size, int max, int* leng){
	int** matr=new int*[size];
	int s=0;
	for(int i=0;i<size;i+=1){
		s=1+rand()%10;
		leng[i]=s;
		matr[i]=new int[s];
		for(int j=0;j<s;j+=1) matr[i][j]=rand()%50;
	}
	return matr;
}

void printt(int **matr, int size, int *leng){
	std::cout<<"Size = "<<size<<std::endl;
	for(int i=0;i<size;i+=1){
		std::cout<<leng[i]<<": ";
		for(int j=0;j<leng[i];j+=1) std::cout<<matr[i][j]<<" ";
		std::cout<<std::endl;
	}
}

int main(){
	srand(time(NULL));
	int size = rand() % 10;
	int MaxValue = 100;
	int *arr = genRandArray(size, MaxValue);
	print(arr,size);
	delete[] arr;
	
	std::cout<<std::endl<<std::endl;
	size=rand()%10;
	int *leng=new int[size];
	int** matrix=genRandMatrix(size, MaxValue,leng);
	printt(matrix,size,leng);
	return 0;
}
